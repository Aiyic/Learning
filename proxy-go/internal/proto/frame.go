// Package proto 定义 proxy_client 与 proxy_serve 之间的内部隧道协议。
//
// 握手阶段(建立隧道时)使用定长头 + 变长字段的帧；握手成功后，
// 隧道两端进入裸字节透明转发(io.Copy 走 sendfile 零拷贝)，不再逐帧封装，
// 这是为了与"零拷贝优先"的策略一致——逐帧封装会破坏 ReadFrom/WriteTo 快路径。
//
// 帧格式(CONNECT 握手帧, client -> server):
//
//	+--------+--------+--------+------------+--------+------------+--------+
//	| Magic  | Ver    | Type   | UserIDLen  | UserID | DstLen     | Dst    |
//	| 2 byte | 1 byte | 1 byte | 2 byte BE  | N byte | 2 byte BE  | M byte |
//	+--------+--------+--------+------------+--------+------------+--------+
//
// 握手响应(server -> client):
//
//	+--------+--------+--------+
//	| Magic  | Ver    | Status |
//	| 2 byte | 1 byte | 1 byte |
//	+--------+--------+--------+
//
// Status: 0x00 = OK, 0x01 = FAIL
package proto

import (
	"encoding/binary"
	"errors"
	"fmt"
	"io"
)

const (
	magic0 byte = 0x50 // 'P'
	magic1 byte = 0x52 // 'R'
	ver         = 0x01

	TypeConnect byte = 0x01
	StatusOK    byte = 0x00
	StatusFail  byte = 0x01

	maxFieldLen = 1 << 16 // UserID/Dst 单字段上限 64KiB
)

// Connect 握手帧内容。
type Connect struct {
	User string // 鉴权用户名，可空
	Dst  string // 目标 host:port
}

// WriteConnect 写入一个 CONNECT 握手帧。
func WriteConnect(w io.Writer, c Connect) error {
	if len(c.User) > maxFieldLen || len(c.Dst) > maxFieldLen {
		return fmt.Errorf("proto: field too long")
	}
	hdr := make([]byte, 6, 6+len(c.User)+2+len(c.Dst))
	hdr[0], hdr[1], hdr[2], hdr[3] = magic0, magic1, ver, TypeConnect
	binary.BigEndian.PutUint16(hdr[4:6], uint16(len(c.User)))
	hdr = append(hdr, c.User...)
	var dstLen [2]byte
	binary.BigEndian.PutUint16(dstLen[:], uint16(len(c.Dst)))
	hdr = append(hdr, dstLen[:]...)
	hdr = append(hdr, c.Dst...)
	_, err := w.Write(hdr)
	return err
}

// ReadConnect 从流中读取并解析一个 CONNECT 握手帧。
func ReadConnect(r io.Reader) (Connect, error) {
	hdr := make([]byte, 6)
	if _, err := io.ReadFull(r, hdr); err != nil {
		return Connect{}, err
	}
	if hdr[0] != magic0 || hdr[1] != magic1 {
		return Connect{}, errors.New("proto: bad magic")
	}
	if hdr[2] != ver {
		return Connect{}, fmt.Errorf("proto: unsupported version %d", hdr[2])
	}
	if hdr[3] != TypeConnect {
		return Connect{}, fmt.Errorf("proto: unexpected type 0x%02x", hdr[3])
	}
	userLen := binary.BigEndian.Uint16(hdr[4:6])

	c := Connect{}
	if userLen > 0 {
		user := make([]byte, userLen)
		if _, err := io.ReadFull(r, user); err != nil {
			return Connect{}, err
		}
		c.User = string(user)
	}

	var dstLen [2]byte
	if _, err := io.ReadFull(r, dstLen[:]); err != nil {
		return Connect{}, err
	}
	dl := binary.BigEndian.Uint16(dstLen[:])
	if dl > 0 {
		dst := make([]byte, dl)
		if _, err := io.ReadFull(r, dst); err != nil {
			return Connect{}, err
		}
		c.Dst = string(dst)
	}
	if c.Dst == "" {
		return Connect{}, errors.New("proto: empty dst")
	}
	return c, nil
}

// WriteStatus 写入握手响应。
func WriteStatus(w io.Writer, status byte) error {
	_, err := w.Write([]byte{magic0, magic1, ver, status})
	return err
}

// ReadStatus 读取握手响应。
func ReadStatus(r io.Reader) (byte, error) {
	hdr := make([]byte, 4)
	if _, err := io.ReadFull(r, hdr); err != nil {
		return StatusFail, err
	}
	if hdr[0] != magic0 || hdr[1] != magic1 || hdr[2] != ver {
		return StatusFail, errors.New("proto: bad response header")
	}
	return hdr[3], nil
}
