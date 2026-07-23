// Package conn 提供 FlowConn —— 在 *net.TCPConn 之上叠加流量统计与活跃度追踪，
// 同时保留 sendfile 零拷贝快路径。
//
// 关键点：FlowConn 实现 io.WriterTo，其 WriteTo 委派给底层 (*net.TCPConn).WriteTo，
// 后者在 dst 也是 *net.TCPConn 时走 sendfile(零拷贝)。io.Copy 优先调用 src.WriteTo，
// 因此两个方向的双向转发都能命中零拷贝，且在 WriteTo 内完成字节计数与活动时间刷新。
package conn

import (
	"io"
	"net"
	"sync/atomic"
	"time"

	"proxy-go/internal/metrics"
)

// FlowConn 包装一条 TCP 连接，叠加统计与活跃度。
type FlowConn struct {
	tcp   *net.TCPConn // 底层 TCP 连接，nil 表示非 TCP(退化，无 sendfile)
	raw   net.Conn     // 通用接口，与 tcp 指向同一连接
	user  string       // 鉴权用户名
	layer string       // "client" | "server"
	dir   string       // 该连接"流出"方向标签："up" | "down"

	bytes    atomic.Int64 // 累计流出字节数
	activity atomic.Int64 // 最近一次数据活动时间(unix nano)
}

// Wrap 包装一条连接。keepalive>0 时启用 TCP keepalive(内核态心跳)。
func Wrap(c net.Conn, layer, user, dir string, keepalive time.Duration) *FlowConn {
	fc := &FlowConn{
		raw:   c,
		user:  user,
		layer: layer,
		dir:   dir,
	}
	fc.activity.Store(time.Now().UnixNano())
	if tcp, ok := c.(*net.TCPConn); ok {
		fc.tcp = tcp
		if keepalive > 0 {
			_ = tcp.SetKeepAlive(true)
			_ = tcp.SetKeepAlivePeriod(keepalive)
		}
	}
	return fc
}

// --- net.Conn 实现 ---

func (c *FlowConn) Read(p []byte) (int, error) {
	n, err := c.raw.Read(p)
	if n > 0 {
		c.touch()
	}
	return n, err
}

func (c *FlowConn) Write(p []byte) (int, error) {
	n, err := c.raw.Write(p)
	if n > 0 {
		// Write 用于少量控制向写入(如 200 响应、转发头)，方向与该连接作为 src
		// 的主数据流相反，不计入字节统计以免标签错位；仅刷新活跃时间。
		c.touch()
	}
	return n, err
}

func (c *FlowConn) Close() error                       { return c.raw.Close() }
func (c *FlowConn) LocalAddr() net.Addr                { return c.raw.LocalAddr() }
func (c *FlowConn) RemoteAddr() net.Addr               { return c.raw.RemoteAddr() }
func (c *FlowConn) SetDeadline(t time.Time) error      { return c.raw.SetDeadline(t) }
func (c *FlowConn) SetReadDeadline(t time.Time) error  { return c.raw.SetReadDeadline(t) }
func (c *FlowConn) SetWriteDeadline(t time.Time) error { return c.raw.SetWriteDeadline(t) }

// --- io.WriterTo：零拷贝 + 计数的核心 ---

// WriteTo 实现 io.WriterTo。当底层为 TCPConn 时走 sendfile 零拷贝，
// 并把成功写入的字节数计入统计与活跃时间。
func (c *FlowConn) WriteTo(w io.Writer) (int64, error) {
	dst := w
	if fc, ok := w.(*FlowConn); ok {
		dst = fc.raw // 解包，让底层 TCPConn.WriteTo 识别 *TCPConn 走 sendfile
	}
	if c.tcp != nil {
		n, err := c.tcp.WriteTo(dst)
		c.addBytes(n)
		return n, err
	}
	// 非 TCP 退化路径：仍计数
	n, err := io.Copy(dst, c.raw)
	c.addBytes(n)
	return n, err
}

// --- 统计与活跃度 ---

func (c *FlowConn) addBytes(n int64) {
	if n <= 0 {
		return
	}
	c.bytes.Add(n)
	c.activity.Store(time.Now().UnixNano())
	metrics.FlowBytes.WithLabelValues(c.layer, c.user, c.dir).Add(float64(n))
}

func (c *FlowConn) touch() {
	c.activity.Store(time.Now().UnixNano())
}

// Bytes 返回累计流出字节数。
func (c *FlowConn) Bytes() int64 { return c.bytes.Load() }

// LastActivityNs 返回最近一次数据活动时间(unix nano)。
func (c *FlowConn) LastActivityNs() int64 { return c.activity.Load() }

// User 返回用户名。
func (c *FlowConn) User() string { return c.user }
