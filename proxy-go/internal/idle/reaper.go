// Package idle 实现基于活跃时间戳的空闲连接回收器，替代原项目的时间轮。
//
// 现代替代思路：不再维护 circular_buffer + 析构 shutdown 的复杂结构，
// 而是由 FlowConn 在每次数据活动时刷新时间戳，reaper 周期扫描注册表，
// 对超过 IdleTimeout 仍无活动的连接直接 Close——这会令阻塞中的 io.Copy
// 立即返回错误，从而拆除整条隧道。
//
// 死连接检测由 TCP keepalive(内核态)负责，与本回收器职责分离：
//   - keepalive：对端崩溃/网络断开 → 内核探活失败 → RST → 连接报错
//   - reaper：连接存活但长期空闲 → 主动回收，控制资源占用
package idle

import (
	"context"
	"sync"
	"time"
)

// Trackable 是回收器跟踪的连接最小接口。
type Trackable interface {
	LastActivityNs() int64
	Close() error
}

// Reaper 周期扫描注册连接，关闭空闲超时者。
type Reaper struct {
	timeout time.Duration
	mu      sync.Mutex
	conns   map[Trackable]struct{}
}

// New 创建回收器。timeout 为空闲超时阈值。
func New(timeout time.Duration) *Reaper {
	return &Reaper{timeout: timeout, conns: make(map[Trackable]struct{})}
}

// Track 注册一条连接。
func (r *Reaper) Track(c Trackable) {
	r.mu.Lock()
	r.conns[c] = struct{}{}
	r.mu.Unlock()
}

// Untrack 注销一条连接(正常关闭后调用)。
func (r *Reaper) Untrack(c Trackable) {
	r.mu.Lock()
	delete(r.conns, c)
	r.mu.Unlock()
}

// Run 启动后台扫描，直到 ctx 取消。扫描间隔为 timeout/2。
func (r *Reaper) Run(ctx context.Context) {
	interval := r.timeout / 2
	if interval < time.Second {
		interval = time.Second
	}
	ticker := time.NewTicker(interval)
	defer ticker.Stop()
	for {
		select {
		case <-ctx.Done():
			return
		case <-ticker.C:
			r.reap()
		}
	}
}

func (r *Reaper) reap() {
	now := time.Now().UnixNano()
	cutoff := now - r.timeout.Nanoseconds()

	// 收集要关闭的连接，避免持锁调用 Close
	r.mu.Lock()
	var victims []Trackable
	for c := range r.conns {
		if c.LastActivityNs() < cutoff {
			victims = append(victims, c)
			delete(r.conns, c)
		}
	}
	r.mu.Unlock()

	for _, c := range victims {
		_ = c.Close()
	}
}
