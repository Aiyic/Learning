// 协程化双向透明转发。
//
// 两个 copy_dir 协程经 awaitable_operators 的 || 并发运行，任一方向结束
// (EOF/错误/超时取消) 即整体结束，随后关闭两端拆除隧道。
// 每个异步操作用 cancel_after(idle, ...) 包裹：有数据则计时器重置，
// 长时间无活动则操作被取消 → 抛 operation_aborted → copy_dir 正常返回。
// 这是 Asio 惯用的"每连接 per-op 空闲超时"，替代时间轮 / 全局 reaper。
//
// 字节计数在 copy_dir 内原子累加，对应 Go 版的 FlowConn 统计。
#pragma once

#include <asio.hpp>
#include <asio/cancel_after.hpp>
#include <asio/experimental/awaitable_operators.hpp>

#include <array>
#include <atomic>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <system_error>

namespace proxy::tunnel {

namespace detail {

inline asio::awaitable<void>
copy_dir(asio::ip::tcp::socket& from, asio::ip::tcp::socket& to,
         std::atomic<std::int64_t>& cnt, std::chrono::seconds idle) {
  std::array<char, 16384> buf{};
  try {
    while (true) {
      std::size_t n = co_await from.async_read_some(
          asio::buffer(buf),
          asio::cancel_after(idle, asio::use_awaitable));
      if (n == 0) co_return; // 对端关闭
      co_await asio::async_write(
          to, asio::buffer(buf, n),
          asio::cancel_after(idle, asio::use_awaitable));
      cnt.fetch_add(static_cast<std::int64_t>(n), std::memory_order_relaxed);
    }
  } catch (const std::system_error&) {
    // EOF / 对端关闭 / 超时取消 / || 取消 —— 均为正常结束
  }
}

} // namespace detail

// 双向转发 a <-> b。任一方向结束即关闭两端。
inline asio::awaitable<void>
pipe(asio::ip::tcp::socket& a, asio::ip::tcp::socket& b,
     std::atomic<std::int64_t>& up, std::atomic<std::int64_t>& down,
     std::chrono::seconds idle) {
  using namespace asio::experimental::awaitable_operators;
  try {
    co_await (detail::copy_dir(a, b, up, idle) ||
              detail::copy_dir(b, a, down, idle));
  } catch (...) {
    // 两侧都失败时 || 可能抛出，忽略
  }
  asio::error_code ignored;
  a.close(ignored);
  b.close(ignored);
}

} // namespace proxy::tunnel
