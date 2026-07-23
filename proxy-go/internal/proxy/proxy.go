// Package proxy 解析面向用户的 HTTP/HTTPS 代理请求。
//
// 支持两种标准代理请求形式：
//   - HTTPS: CONNECT host:port HTTP/1.1  (+ Proxy-Authorization)
//   - HTTP:  GET http://host/path HTTP/1.1 (绝对 URI) 或带 Host 头的 origin-form
//
// 鉴权头 Proxy-Authorization 由调用方交给 auth 包校验。HTTP 请求转发时，
// 会剥除代理专有头(Proxy-Authorization / Proxy-Connection) 并将绝对 URI
// 转为 origin-form(/path)，符合上游服务器期望。
package proxy

import (
	"bufio"
	"errors"
	"fmt"
	"io"
	"net/url"
	"strings"
)

const maxHeadSize = 64 * 1024 // 请求头上限，防止恶意超大头撑爆内存

// Request 解析结果。
type Request struct {
	Method     string // "CONNECT" 或 HTTP 方法
	Target     string // 目标 host:port
	IsConnect  bool
	AuthUser   string // 鉴权通过后的用户名(由 ParseRequest 调 auth 填入)
	authHeader string // Proxy-Authorization 原始值

	// forwardHead 是 HTTP 转发时应先发给上游的请求头字节(CONNECT 为 nil)。
	forwardHead []byte
	// br 持有读出 head 后的 bufio.Reader，其中可能残留请求体字节。
	br *bufio.Reader
}

// BufferedBody 返回已读入 bufio 缓冲但尚未转发的字节数(请求体前段)。
func (r *Request) BufferedBody() int {
	if r.br == nil {
		return 0
	}
	return r.br.Buffered()
}

// DrainBuffered 把 bufio 中残留字节写入 w，并返回写入数。
func (r *Request) DrainBuffered(w io.Writer) (int, error) {
	if r.br == nil {
		return 0, nil
	}
	n := r.br.Buffered()
	if n == 0 {
		return 0, nil
	}
	b, err := r.br.Peek(n)
	if err != nil {
		return 0, err
	}
	if _, err := w.Write(b); err != nil {
		return 0, err
	}
	_, _ = r.br.Discard(n)
	return n, nil
}

// ForwardHead 返回 HTTP 转发头(CONNECT 返回 nil)。
func (r *Request) ForwardHead() []byte { return r.forwardHead }

// AuthHeader 返回 Proxy-Authorization 原始值，供 auth 校验。
func (r *Request) AuthHeader() string { return r.authHeader }

// ParseRequest 从 br 读取并解析一个代理请求头。
func ParseRequest(br *bufio.Reader) (*Request, error) {
	// 读到 \r\n\r\n 为止，累计为原始头字节。
	var raw []byte
	for {
		line, err := br.ReadBytes('\n')
		if err != nil {
			return nil, err
		}
		raw = append(raw, line...)
		if len(raw) > maxHeadSize {
			return nil, errors.New("proxy: request head too large")
		}
		// 头以空行(\r\n)结束
		if len(raw) >= 4 && string(raw[len(raw)-4:]) == "\r\n\r\n" {
			break
		}
	}

	lines := strings.Split(string(raw[:len(raw)-4]), "\r\n")
	if len(lines) == 0 {
		return nil, errors.New("proxy: empty request")
	}

	req := &Request{br: br}
	parts := strings.Fields(lines[0])
	if len(parts) < 3 {
		return nil, fmt.Errorf("proxy: bad request line: %q", lines[0])
	}
	req.Method = parts[0]
	uri := parts[1]
	proto := parts[2]

	// 解析 headers(保留顺序)，收集 Host 与 Proxy-Authorization。
	var host string
	var kept []string // 保留并转发的头
	for _, h := range lines[1:] {
		if h == "" {
			continue
		}
		name, val, ok := strings.Cut(h, ":")
		if !ok {
			continue
		}
		name = strings.TrimSpace(name)
		val = strings.TrimSpace(val)
		lname := strings.ToLower(name)
		switch lname {
		case "host":
			host = val
			kept = append(kept, name+": "+val)
		case "proxy-authorization":
			req.authHeader = val // 不转发
		case "proxy-connection":
			// 丢弃，避免泄露给上游
		default:
			kept = append(kept, name+": "+val)
		}
	}

	if req.Method == "CONNECT" {
		req.IsConnect = true
		req.Target = uri // CONNECT 的 URI 即 host:port
		return req, nil
	}

	// HTTP: 处理绝对 URI → origin-form，并确定目标 host:port。
	originURI := uri
	if strings.Contains(uri, "://") {
		u, err := url.Parse(uri)
		if err != nil {
			return nil, fmt.Errorf("proxy: bad absolute URI: %w", err)
		}
		if u.Host == "" {
			return nil, errors.New("proxy: absolute URI without host")
		}
		req.Target = u.Host
		originURI = u.RequestURI()
		if !strings.Contains(req.Target, ":") {
			req.Target += ":80"
		}
	} else {
		// origin-form: 目标来自 Host 头
		if host == "" {
			return nil, errors.New("proxy: HTTP request without Host")
		}
		req.Target = host
		if !strings.Contains(host, ":") {
			req.Target += ":80"
		}
	}

	// 重建转发头：请求行(origin-form) + 保留头 + 空行。
	var b strings.Builder
	b.WriteString(req.Method + " " + originURI + " " + proto + "\r\n")
	for _, h := range kept {
		b.WriteString(h + "\r\n")
	}
	b.WriteString("\r\n")
	req.forwardHead = []byte(b.String())
	return req, nil
}
