// Package config 加载运行配置。
//
// 现代实践：优先环境变量，并提供结构体默认值，避免硬编码。
// 不引入第三方配置库，保持零额外依赖心智。
package config

import (
	"fmt"
	"os"
	"strconv"
	"strings"
	"time"
)

// Config 汇总两级服务的运行参数。
type Config struct {
	LogLevel string

	// 接入层 proxy_client
	Client struct {
		HTTPAddr    string            // 面向用户的 HTTP 代理监听地址
		HTTPSAddr   string            // 面向用户的 HTTPS(CONNECT) 代理监听地址
		ServerAddr  string            // 上游 proxy_serve 地址
		MetricsAddr string            // /metrics 暴露地址
		DialTimeout time.Duration     // 拨号 proxy_serve 超时
		IdleTimeout time.Duration     // 空闲连接超时
		KeepAlive   time.Duration     // TCP keepalive 探测周期
		MaxConns    int               // 最大并发连接数
		Users       map[string]string // user -> pass，空表示免鉴权
	}

	// 出口层 proxy_serve
	Server struct {
		TunnelAddr  string        // 接收 proxy_client 隧道连接的监听地址
		MetricsAddr string        // /metrics 暴露地址
		DialTimeout time.Duration // 拨号目标服务器超时
		IdleTimeout time.Duration // 空闲连接超时
		KeepAlive   time.Duration // TCP keepalive 探测周期
		MaxConns    int           // 最大并发连接数
	}
}

// FromEnv 从环境变量读取配置，缺省值兜底。
func FromEnv() (*Config, error) {
	c := &Config{LogLevel: getenv("LOG_LEVEL", "info")}

	c.Client.HTTPAddr = getenv("CLIENT_HTTP_ADDR", ":12346")
	c.Client.HTTPSAddr = getenv("CLIENT_HTTPS_ADDR", ":12345")
	c.Client.ServerAddr = getenv("CLIENT_SERVER_ADDR", "127.0.0.1:23456")
	c.Client.MetricsAddr = getenv("CLIENT_METRICS_ADDR", ":9091")
	c.Client.DialTimeout = getenvDur("CLIENT_DIAL_TIMEOUT", 5*time.Second)
	c.Client.IdleTimeout = getenvDur("CLIENT_IDLE_TIMEOUT", 120*time.Second)
	c.Client.KeepAlive = getenvDur("CLIENT_KEEPALIVE", 30*time.Second)
	c.Client.MaxConns = getenvInt("CLIENT_MAX_CONNS", 1000000)
	c.Client.Users = parseUsers(getenv("CLIENT_USERS", "")) // "user1:pass1,user2:pass2"

	c.Server.TunnelAddr = getenv("SERVER_TUNNEL_ADDR", ":23456")
	c.Server.MetricsAddr = getenv("SERVER_METRICS_ADDR", ":9090")
	c.Server.DialTimeout = getenvDur("SERVER_DIAL_TIMEOUT", 5*time.Second)
	c.Server.IdleTimeout = getenvDur("SERVER_IDLE_TIMEOUT", 120*time.Second)
	c.Server.KeepAlive = getenvDur("SERVER_KEEPALIVE", 30*time.Second)
	c.Server.MaxConns = getenvInt("SERVER_MAX_CONNS", 1000000)

	if c.Server.MaxConns <= 0 {
		return nil, fmt.Errorf("SERVER_MAX_CONNS must be positive")
	}
	if c.Client.MaxConns <= 0 {
		return nil, fmt.Errorf("CLIENT_MAX_CONNS must be positive")
	}
	return c, nil
}

func getenv(k, def string) string {
	if v, ok := os.LookupEnv(k); ok && v != "" {
		return v
	}
	return def
}

func getenvDur(k string, def time.Duration) time.Duration {
	if v, ok := os.LookupEnv(k); ok && v != "" {
		if d, err := time.ParseDuration(v); err == nil {
			return d
		}
	}
	return def
}

func getenvInt(k string, def int) int {
	if v, ok := os.LookupEnv(k); ok && v != "" {
		if n, err := strconv.Atoi(v); err == nil {
			return n
		}
	}
	return def
}

// parseUsers 解析 "u1:p1,u2:p2" 形式的用户表。
func parseUsers(s string) map[string]string {
	if s == "" {
		return nil
	}
	m := map[string]string{}
	for _, pair := range strings.Split(s, ",") {
		if k, v, ok := strings.Cut(pair, ":"); ok {
			m[strings.TrimSpace(k)] = strings.TrimSpace(v)
		}
	}
	return m
}
