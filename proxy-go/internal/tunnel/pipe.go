// Package tunnel 实现两个 FlowConn 之间的双向透明转发。
//
// 双向各跑一个 io.Copy；由于 FlowConn 实现了 io.WriterTo，io.Copy 会调用
// src.WriteTo 走 sendfile 零拷贝路径，并在其中完成字节计数。任一方向结束
// (EOF 或错误)即关闭两端连接，使另一方向的 io.Copy 立即返回，拆除隧道。
package tunnel

import (
	"io"
	"sync"

	"proxy-go/internal/conn"
)

// Pipe 双向转发 a <-> b，返回 (a→b, b→a) 的字节数。
// 该函数在两条转发都结束后才返回。
func Pipe(a, b *conn.FlowConn) (int64, int64) {
	var aToB, bToA int64
	var wg sync.WaitGroup
	wg.Add(2)

	// a → b
	go func() {
		defer wg.Done()
		aToB, _ = io.Copy(b, a) // src=a，命中 a.WriteTo → sendfile，计入 a.dir
		_ = a.Close()
		_ = b.Close()
	}()
	// b → a
	go func() {
		defer wg.Done()
		bToA, _ = io.Copy(a, b) // src=b，命中 b.WriteTo → sendfile，计入 b.dir
		_ = a.Close()
		_ = b.Close()
	}()

	wg.Wait()
	return aToB, bToA
}
