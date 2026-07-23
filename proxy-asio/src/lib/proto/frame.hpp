// 两级间隧道帧协议(协程化读写)。
//
// 帧格式与 Go 版一致：
//   CONNECT 帧:  Magic(2) Ver(1) Type(1) UserIDLen(2 BE) UserID DstLen(2 BE) Dst
//   状态响应:     Magic(2) Ver(1) Status(1)
//
// 握手成功后进入裸字节透明转发(见 tunnel/pipe.hpp)，不再逐帧封装。
#pragma once

#include <asio.hpp>

#include <array>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <utility>

namespace proxy::proto {

inline constexpr std::uint8_t kMagic0 = 0x50; // 'P'
inline constexpr std::uint8_t kMagic1 = 0x52; // 'R'
inline constexpr std::uint8_t kVer = 0x01;

inline constexpr std::uint8_t kTypeConnect = 0x01;
inline constexpr std::uint8_t kStatusOK = 0x00;
inline constexpr std::uint8_t kStatusFail = 0x01;

inline constexpr std::size_t kMaxFieldLen = 1 << 16;

struct Connect {
  std::string user; // 可空
  std::string dst;  // host:port
};

namespace detail {
inline void put16(std::string& s, std::uint16_t v) {
  s.push_back(static_cast<char>((v >> 8) & 0xff));
  s.push_back(static_cast<char>(v & 0xff));
}
} // namespace detail

inline asio::awaitable<void>
write_connect(asio::ip::tcp::socket& s, const Connect& c) {
  if (c.user.size() > kMaxFieldLen || c.dst.size() > kMaxFieldLen)
    throw std::length_error("proto: field too long");

  std::string frame;
  frame.reserve(6 + c.user.size() + 2 + c.dst.size());
  frame.push_back(static_cast<char>(kMagic0));
  frame.push_back(static_cast<char>(kMagic1));
  frame.push_back(static_cast<char>(kVer));
  frame.push_back(static_cast<char>(kTypeConnect));
  detail::put16(frame, static_cast<std::uint16_t>(c.user.size()));
  frame += c.user;
  detail::put16(frame, static_cast<std::uint16_t>(c.dst.size()));
  frame += c.dst;

  co_await asio::async_write(s, asio::buffer(frame), asio::transfer_all(),
                             asio::use_awaitable);
}

inline asio::awaitable<Connect>
read_connect(asio::ip::tcp::socket& s) {
  std::array<std::uint8_t, 6> hdr{};
  co_await asio::async_read(s, asio::buffer(hdr),
                            asio::transfer_exactly(hdr.size()), asio::use_awaitable);

  if (hdr[0] != kMagic0 || hdr[1] != kMagic1)
    throw std::runtime_error("proto: bad magic");
  if (hdr[2] != kVer)
    throw std::runtime_error("proto: bad version");
  if (hdr[3] != kTypeConnect)
    throw std::runtime_error("proto: bad type");

  Connect c;
  std::uint16_t ulen = static_cast<std::uint16_t>((hdr[4] << 8) | hdr[5]);
  if (ulen > 0) {
    c.user.resize(ulen);
    co_await asio::async_read(s, asio::buffer(c.user),
                              asio::transfer_exactly(ulen), asio::use_awaitable);
  }

  std::array<std::uint8_t, 2> dl{};
  co_await asio::async_read(s, asio::buffer(dl),
                            asio::transfer_exactly(dl.size()), asio::use_awaitable);
  std::uint16_t dlen = static_cast<std::uint16_t>((dl[0] << 8) | dl[1]);
  if (dlen == 0) throw std::runtime_error("proto: empty dst");
  c.dst.resize(dlen);
  co_await asio::async_read(s, asio::buffer(c.dst),
                            asio::transfer_exactly(dlen), asio::use_awaitable);
  co_return c;
}

inline asio::awaitable<void>
write_status(asio::ip::tcp::socket& s, std::uint8_t status) {
  std::uint8_t buf[4] = {kMagic0, kMagic1, kVer, status};
  co_await asio::async_write(s, asio::buffer(buf), asio::transfer_all(),
                             asio::use_awaitable);
}

// 状态帧原始字节，用于无法 co_await 的场景(如 catch 块)下同步写入。
inline std::array<std::uint8_t, 4> status_frame(std::uint8_t status) {
  return {kMagic0, kMagic1, kVer, status};
}

inline asio::awaitable<std::uint8_t>
read_status(asio::ip::tcp::socket& s) {
  std::array<std::uint8_t, 4> buf{};
  co_await asio::async_read(s, asio::buffer(buf),
                            asio::transfer_exactly(buf.size()), asio::use_awaitable);
  if (buf[0] != kMagic0 || buf[1] != kMagic1 || buf[2] != kVer)
    throw std::runtime_error("proto: bad status header");
  co_return buf[3];
}

} // namespace proxy::proto
