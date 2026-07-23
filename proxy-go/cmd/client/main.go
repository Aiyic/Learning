// Command proxy_client 是接入层：面向用户监听 HTTP(:12346) / HTTPS(:12345) 代理，
// 鉴权并解析目标后，通过内部隧道协议把流量转给上游 proxy_serve。
package main

import (
	"bufio"
	"context"
	"errors"
	"io"
	"log/slog"
	"net"
	"net/http"
	"os"
	"os/signal"
	"sync/atomic"
	"syscall"
	"time"

	"github.com/prometheus/client_golang/prometheus/promhttp"

	"proxy-go/internal/auth"
	"proxy-go/internal/config"
	"proxy-go/internal/conn"
	"proxy-go/internal/idle"
	pkglog "proxy-go/internal/log"
	"proxy-go/internal/metrics"
	"proxy-go/internal/proto"
	"proxy-go/internal/proxy"
	"proxy-go/internal/tunnel"
)

func main() {
	cfg, err := config.FromEnv()
	if err != nil {
		panic(err)
	}
	pkglog.Init(cfg.LogLevel)

	authn := auth.New(cfg.Client.Users)
	reaper := idle.New(cfg.Client.IdleTimeout)

	ctx, stop := signal.NotifyContext(context.Background(), os.Interrupt, syscall.SIGTERM)
	defer stop()

	go serveMetrics(cfg.Client.MetricsAddr)
	go reaper.Run(ctx)

	var conns atomic.Int32

	// HTTPS (CONNECT) 监听
	httpsLn, err := net.Listen("tcp", cfg.Client.HTTPSAddr)
	if err != nil {
		slog.Error("listen https failed", "addr", cfg.Client.HTTPSAddr, "err", err)
		os.Exit(1)
	}
	// HTTP 监听
	httpLn, err := net.Listen("tcp", cfg.Client.HTTPAddr)
	if err != nil {
		slog.Error("listen http failed", "addr", cfg.Client.HTTPAddr, "err", err)
		os.Exit(1)
	}

	slog.Info("proxy_client listening",
		"https", cfg.Client.HTTPSAddr, "http", cfg.Client.HTTPAddr,
		"upstream", cfg.Client.ServerAddr,
		"auth", len(cfg.Client.Users) > 0)

	go acceptLoop(ctx, httpsLn, cfg, authn, reaper, &conns, true)
	go acceptLoop(ctx, httpLn, cfg, authn, reaper, &conns, false)

	<-ctx.Done()
	slog.Info("proxy_client shutting down")
	_ = httpsLn.Close()
	_ = httpLn.Close()
	time.Sleep(200 * time.Millisecond)
}

func acceptLoop(ctx context.Context, ln net.Listener, cfg *config.Config, authn *auth.Authenticator,
	reaper *idle.Reaper, conns *atomic.Int32, isHTTPS bool) {
	for {
		c, err := ln.Accept()
		if err != nil {
			if ctx.Err() != nil || errors.Is(err, net.ErrClosed) {
				return
			}
			slog.Warn("accept failed", "err", err)
			continue
		}
		if int(conns.Add(1)) > cfg.Client.MaxConns {
			conns.Add(-1)
			slog.Warn("max connections reached, rejecting", "max", cfg.Client.MaxConns)
			_ = c.Close()
			continue
		}
		go handle(ctx, c, cfg, authn, reaper, conns, isHTTPS)
	}
}

func handle(ctx context.Context, uc net.Conn, cfg *config.Config, authn *auth.Authenticator,
	reaper *idle.Reaper, conns *atomic.Int32, isHTTPS bool) {
	defer conns.Add(-1)
	defer uc.Close()
	start := time.Now()

	br := bufio.NewReader(uc)

	// 1. 解析代理请求头
	req, err := proxy.ParseRequest(br)
	if err != nil {
		slog.Debug("parse request failed", "err", err)
		return
	}
	pl := protoLabel(req)

	// 2. 鉴权
	user, err := authn.Authenticate(req.AuthHeader())
	if err != nil {
		_ = proxy.WriteAuthRequired(uc, "proxy")
		metrics.Requests.WithLabelValues("client", auth.Anonymous, pl, "authfail").Inc()
		return
	}

	// 3. 拨号上游 proxy_serve
	dctx, cancel := context.WithTimeout(ctx, cfg.Client.DialTimeout)
	tc, err := (&net.Dialer{}).DialContext(dctx, "tcp", cfg.Client.ServerAddr)
	cancel()
	if err != nil {
		if req.IsConnect {
			_ = proxy.WriteBadGateway(uc)
		}
		metrics.Requests.WithLabelValues("client", user, pl, "dialfail").Inc()
		return
	}
	defer tc.Close()

	// 4. 隧道握手：发 CONNECT 帧，读状态
	if err := proto.WriteConnect(tc, proto.Connect{User: user, Dst: req.Target}); err != nil {
		slog.Debug("write connect frame failed", "err", err)
		return
	}
	status, err := proto.ReadStatus(tc)
	if err != nil || status != proto.StatusOK {
		if req.IsConnect {
			_ = proxy.WriteBadGateway(uc)
		}
		metrics.Requests.WithLabelValues("client", user, pl, "tunnelfail").Inc()
		return
	}

	// 5. 包装连接：user(dir=up：用户→隧道) / tunnel(dir=down：隧道→用户)
	userFlow := conn.Wrap(uc, "client", user, "up", cfg.Client.KeepAlive)
	tunnelFlow := conn.Wrap(tc, "client", user, "down", cfg.Client.KeepAlive)

	// 6. 协议特定收尾
	if req.IsConnect {
		if err := proxy.WriteConnectOK(userFlow); err != nil {
			return
		}
	} else {
		// HTTP：先把转发头发给上游
		if err := writeAll(tunnelFlow, req.ForwardHead()); err != nil {
			return
		}
	}
	// 把 bufio 中已读入的残留字节(请求体/流水线 TLS 握手)转发给上游
	if _, err := req.DrainBuffered(tunnelFlow); err != nil {
		return
	}

	reaper.Track(userFlow)
	reaper.Track(tunnelFlow)
	defer reaper.Untrack(userFlow)
	defer reaper.Untrack(tunnelFlow)

	metrics.ActiveConnections.WithLabelValues("client").Inc()
	defer metrics.ActiveConnections.WithLabelValues("client").Dec()

	// 7. 双向零拷贝转发
	up, down := tunnel.Pipe(userFlow, tunnelFlow)

	metrics.ConnDuration.WithLabelValues("client", pl).Observe(time.Since(start).Seconds())
	metrics.Requests.WithLabelValues("client", user, pl, "ok").Inc()
	slog.Debug("conn closed", "user", user, "dst", req.Target,
		"up", up, "down", down, "dur", time.Since(start))
}

func protoLabel(r *proxy.Request) string {
	if r.IsConnect {
		return "https"
	}
	return "http"
}

// writeAll 完整写入所有字节，处理短写。
func writeAll(w io.Writer, b []byte) error {
	for len(b) > 0 {
		n, err := w.Write(b)
		if err != nil {
			return err
		}
		b = b[n:]
	}
	return nil
}

func serveMetrics(addr string) {
	mux := http.NewServeMux()
	mux.Handle("/metrics", promhttp.Handler())
	srv := &http.Server{Addr: addr, Handler: mux, ReadHeaderTimeout: 5 * time.Second}
	slog.Info("metrics server listening", "addr", addr)
	if err := srv.ListenAndServe(); err != nil && !errors.Is(err, http.ErrServerClosed) {
		slog.Error("metrics server error", "err", err)
	}
}
