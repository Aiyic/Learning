package proxy

import "fmt"

// 面向用户的代理响应构造。写回客户端 conn，遵循 HTTP/1.1。

// WriteConnectOK 写 HTTPS 隧道建立成功响应。
func WriteConnectOK(w interface{ Write([]byte) (int, error) }) error {
	_, err := w.Write([]byte("HTTP/1.1 200 Connection Established\r\n\r\n"))
	return err
}

// WriteAuthRequired 写 407 需要代理鉴权，带 Basic challenge。
func WriteAuthRequired(w interface{ Write([]byte) (int, error) }, realm string) error {
	if realm == "" {
		realm = "proxy"
	}
	body := "Proxy Authentication Required\n"
	resp := fmt.Sprintf(
		"HTTP/1.1 407 Proxy Authentication Required\r\n"+
			"Proxy-Authenticate: Basic realm=%q\r\n"+
			"Content-Type: text/plain; charset=utf-8\r\n"+
			"Content-Length: %d\r\n"+
			"Connection: close\r\n\r\n%s",
		realm, len(body), body)
	_, err := w.Write([]byte(resp))
	return err
}

// WriteBadGateway 写 502，用于目标不可达等失败。
func WriteBadGateway(w interface{ Write([]byte) (int, error) }) error {
	body := "Bad Gateway\n"
	resp := fmt.Sprintf(
		"HTTP/1.1 502 Bad Gateway\r\n"+
			"Content-Type: text/plain; charset=utf-8\r\n"+
			"Content-Length: %d\r\n"+
			"Connection: close\r\n\r\n%s", len(body), body)
	_, err := w.Write([]byte(resp))
	return err
}
