// 网络小工具：地址拆分与异步解析。
#pragma once

#include <asio.hpp>

#include <string>
#include <string_view>
#include <utility>

namespace proxy::net {

// 拆分 host:port，兼容 [ipv6]:port 形式。
inline std::pair<std::string, std::string>
split_host_port(std::string_view addr) {
  if (!addr.empty() && addr.front() == '[') {
    if (auto rb = addr.find(']'); rb != std::string_view::npos) {
      std::string host(addr.substr(1, rb - 1));
      std::string port;
      if (rb + 1 < addr.size() && addr[rb + 1] == ':')
        port = std::string(addr.substr(rb + 2));
      return {std::move(host), std::move(port)};
    }
  }
  auto colon = addr.rfind(':');
  if (colon == std::string_view::npos) return {std::string(addr), std::string()};
  return {std::string(addr.substr(0, colon)), std::string(addr.substr(colon + 1))};
}

// 协程化 DNS 解析 host:port -> endpoints。
inline asio::awaitable<asio::ip::tcp::resolver::results_type>
resolve(std::string_view addr) {
  auto exec = co_await asio::this_coro::executor;
  asio::ip::tcp::resolver r(exec);
  auto [host, port] = split_host_port(addr);
  co_return co_await r.async_resolve(host, port, asio::use_awaitable);
}

// 同步解析监听地址 -> endpoint(仅启动时调用)。
// 空 host 监听所有 IPv4 接口(0.0.0.0)。
inline asio::ip::tcp::endpoint
make_endpoint(asio::io_context& ioc, const std::string& addr) {
  auto [host, port] = split_host_port(addr);
  if (host.empty()) host = "0.0.0.0";
  if (port.empty()) port = "0";
  asio::ip::tcp::resolver r(ioc);
  auto results = r.resolve(host, port);
  return *results.begin();
}

} // namespace proxy::net
