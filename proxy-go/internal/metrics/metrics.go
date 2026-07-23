// Package metrics 定义 Prometheus 指标并通过 /metrics 暴露。
package metrics

import (
	"github.com/prometheus/client_golang/prometheus"
	"github.com/prometheus/client_golang/prometheus/promauto"
)

// 指标维度说明：
//   - layer: "client" | "server"  接入层 / 出口层
//   - dir:   "up" | "down"        上行(用户→目标) / 下行(目标→用户)
//   - user:  鉴权用户名，未鉴权为 "anonymous"
//   - proto: "http" | "https"
var (
	// ActiveConnections 当前活跃连接数(Gauge)
	ActiveConnections = promauto.NewGaugeVec(prometheus.GaugeOpts{
		Name: "proxy_active_connections",
		Help: "Current active connections.",
	}, []string{"layer"})

	// FlowBytes 累计转发字节数(Counter)
	FlowBytes = promauto.NewCounterVec(prometheus.CounterOpts{
		Name: "proxy_bytes_total",
		Help: "Total bytes proxied.",
	}, []string{"layer", "user", "dir"})

	// Requests 累计代理请求数(Counter)
	Requests = promauto.NewCounterVec(prometheus.CounterOpts{
		Name: "proxy_requests_total",
		Help: "Total proxied requests.",
	}, []string{"layer", "user", "proto", "result"})

	// ConnDuration 连接持续时长直方图(秒)
	ConnDuration = promauto.NewHistogramVec(prometheus.HistogramOpts{
		Name:    "proxy_conn_duration_seconds",
		Help:    "Connection duration in seconds.",
		Buckets: prometheus.ExponentialBuckets(0.01, 2, 12), // 10ms ~ ~40s
	}, []string{"layer", "proto"})
)
