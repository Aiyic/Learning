// Package auth 处理面向用户的代理鉴权(Proxy-Authorization: Basic)。
package auth

import (
	"encoding/base64"
	"errors"
	"strings"
)

// Authenticator 校验用户凭据。users 为空表示免鉴权(用户名记为 anonymous)。
type Authenticator struct {
	users map[string]string
}

func New(users map[string]string) *Authenticator {
	return &Authenticator{users: users}
}

// Anonymous 表示免鉴权场景下的用户名。
const Anonymous = "anonymous"

// Authenticate 校验 Proxy-Authorization 头的值，返回用户名。
//   - header 为空：若配置了用户表则返回错误，否则返回 Anonymous
//   - "Basic <b64>"：解出 user:pass 校验
func (a *Authenticator) Authenticate(header string) (string, error) {
	if header == "" {
		if len(a.users) == 0 {
			return Anonymous, nil
		}
		return "", errors.New("auth: proxy authentication required")
	}

	const prefix = "Basic "
	if !strings.HasPrefix(header, prefix) {
		return "", errors.New("auth: unsupported scheme")
	}
	dec, err := base64.StdEncoding.DecodeString(strings.TrimSpace(header[len(prefix):]))
	if err != nil {
		return "", errors.New("auth: bad base64")
	}
	user, pass, ok := strings.Cut(string(dec), ":")
	if !ok {
		return "", errors.New("auth: bad credential format")
	}
	if len(a.users) == 0 {
		return user, nil // 配置免鉴权但客户端带了凭据，接受其用户名
	}
	want, ok := a.users[user]
	if !ok || want != pass {
		return "", errors.New("auth: invalid credential")
	}
	return user, nil
}
