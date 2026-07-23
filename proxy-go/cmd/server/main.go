// Command proxy_serve 是出口层：接收来自 proxy_client 的隧道连接，
// 解析目标地址后拨号真实服务器，双向透明转发。
package main

import (
	"context"
	"errors"
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
	"proxy-go/internal/tunnel"
)

func main() {
	cfg, err := config.FromEnv()
	if err != nil {
		panic(err)
	}
	pkglog.Init(cfg.LogLevel)

	ctx, stop := signal.NotifyContext(context.Background(), os.Interrupt, syscall.SIGTERM)
	defer stop()

	go serveMetrics(cfg.Server.MetricsAddr)

	reaper := idle.New(cfg.Server.IdleTimeout)
	go reaper.Run(ctx)

	ln, err := net.Listen("tcp", cfg.Server.TunnelAddr)
	if err != nil {
		slog.Error("listen failed", "addr", cfg.Server.TunnelAddr, "err", err)
		os.Exit(1)
	}
	slog.Info("proxy_serve listening", "addr", cfg.Server.TunnelAddr,
		"idle", cfg.Server.IdleTimeout, "keepalive", cfg.Server.KeepAlive)

	var conns atomic.Int32
	go acceptLoop(ctx, ln, cfg, reaper, &conns)

	<-ctx.Done()
	slog.Info("proxy_serve shutting down")
	_ = ln.Close()
	// 给在飞连接一点时间优雅收尾
	time.Sleep(200 * time.Millisecond)
}

func acceptLoop(ctx context.Context, ln net.Listener, cfg *config.Config, reaper *idle.Reaper, conns *atomic.Int32) {
	for {
		c, err := ln.Accept()
		if err != nil {
			if ctx.Err() != nil {
				return
			}
			if errors.Is(err, net.ErrClosed) {
				return
			}
			slog.Warn("accept failed", "err", err)
			continue
		}
		if int(conns.Add(1)) > cfg.Server.MaxConns {
			conns.Add(-1)
			slog.Warn("max connections reached, rejecting", "max", cfg.Server.MaxConns)
			_ = c.Close()
			continue
		}
		go handle(ctx, c, cfg, reaper, conns)
	}
}

func handle(ctx context.Context, c net.Conn, cfg *config.Config, reaper *idle.Reaper, conns *atomic.Int32) {
	defer conns.Add(-1)
	defer c.Close()
	start := time.Now()

	// 1. 读取 CONNECT 握手帧 → user + dst
	connReq, err := proto.ReadConnect(c)
	if err != nil {
		slog.Debug("read connect frame failed", "err", err)
		return
	}
	user := connReq.User
	if user == "" {
		user = auth.Anonymous
	}

	// 2. 包装隧道连接(dir=up：隧道→目标 即上行)
	tunnelFlow := conn.Wrap(c, "server", user, "up", cfg.Server.KeepAlive)

	// 3. 拨号目标服务器
	dctx, cancel := context.WithTimeout(ctx, cfg.Server.DialTimeout)
	target, err := (&net.Dialer{}).DialContext(dctx, "tcp", connReq.Dst)
	cancel()
	if err != nil {
		slog.Info("dial target failed", "dst", connReq.Dst, "err", err)
		_ = proto.WriteStatus(tunnelFlow, proto.StatusFail)
		metrics.Requests.WithLabelValues("server", user, "tunnel", "dialfail").Inc()
		return
	}
	defer target.Close()

	// 4. 握手成功
	if err := proto.WriteStatus(tunnelFlow, proto.StatusOK); err != nil {
		slog.Debug("write status failed", "err", err)
		return
	}

	// 5. 包装目标连接(dir=down：目标→隧道 即下行)
	targetFlow := conn.Wrap(target, "server", user, "down", cfg.Server.KeepAlive)

	reaper.Track(tunnelFlow)
	reaper.Track(targetFlow)
	defer reaper.Untrack(tunnelFlow)
	defer reaper.Untrack(targetFlow)

	metrics.ActiveConnections.WithLabelValues("server").Inc()
	defer metrics.ActiveConnections.WithLabelValues("server").Dec()

	// 6. 双向零拷贝转发
	up, down := tunnel.Pipe(tunnelFlow, targetFlow)

	metrics.ConnDuration.WithLabelValues("server", "tunnel").Observe(time.Since(start).Seconds())
	metrics.Requests.WithLabelValues("server", user, "tunnel", "ok").Inc()
	slog.Debug("conn closed", "user", user, "dst", connReq.Dst,
		"up", up, "down", down, "dur", time.Since(start))
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
