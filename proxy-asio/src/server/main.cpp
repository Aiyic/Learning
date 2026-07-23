// proxy_serve：出口层。接收 proxy_client 的隧道连接，解析目标后拨号真实服务器，
// 双向透明转发。每个连接一个协程，跑在独立 strand 上以保证线程安全。
#include <asio.hpp>
#include <spdlog/spdlog.h>

#include <atomic>
#include <chrono>
#include <csignal>
#include <exception>
#include <memory>
#include <thread>
#include <vector>

#include "auth/auth.hpp"
#include "config/config.hpp"
#include "log/log.hpp"
#include "net.hpp"
#include "proto/frame.hpp"
#include "tunnel/pipe.hpp"

#ifdef _WIN32
#include <process.h>
#define PROXY_GETPID() _getpid()
#else
#include <unistd.h>
#define PROXY_GETPID() getpid()
#endif

using asio::awaitable;
using asio::ip::tcp;
using namespace proxy;
using namespace std::chrono;

namespace {

// 连接计数 RAII 守卫，确保任意退出路径都正确递减。
struct ConnGuard {
  std::atomic<int>& c;
  ~ConnGuard() { c.fetch_sub(1); }
};

class ProxyServer {
public:
  ProxyServer(asio::io_context& ioc, const config::ServerConfig& cfg)
      : ioc_(ioc), cfg_(cfg) {}

  awaitable<void> listen() {
    tcp::acceptor acc(ioc_, net::make_endpoint(ioc_, cfg_.tunnel_addr));
    acc.set_option(asio::socket_base::reuse_address(true));
    spdlog::info("proxy_serve listening on {} idle={}s keepalive={}s",
                 cfg_.tunnel_addr, cfg_.idle_timeout_sec, cfg_.keepalive_sec);

    while (true) {
      auto strand = asio::make_strand(ioc_);
      tcp::socket peer(strand);
      std::error_code ec;
      co_await acc.async_accept(peer,
                                asio::redirect_error(asio::use_awaitable, ec));
      if (ec) {
        if (ioc_.stopped()) co_return;
        spdlog::warn("accept: {}", ec.message());
        continue;
      }
      if (conns_.fetch_add(1) + 1 > cfg_.max_conns) {
        conns_.fetch_sub(1);
        peer.close();
        continue;
      }
      asio::co_spawn(strand, handle_tunnel(std::move(peer)), asio::detached);
    }
  }

  awaitable<void> handle_tunnel(tcp::socket peer) {
    ConnGuard guard{conns_};
    auto exec = co_await asio::this_coro::executor;
    seconds idle(cfg_.idle_timeout_sec);

    asio::error_code opt_ec;
    peer.set_option(asio::socket_base::keep_alive(true), opt_ec);

    try {
      // 1. 读取 CONNECT 握手帧
      auto conn = co_await proto::read_connect(peer);
      std::string user = conn.user.empty() ? std::string(auth::Anonymous) : conn.user;

      // 2. 拨号目标
      tcp::socket target(exec);
      try {
        auto endpoints = co_await net::resolve(conn.dst);
        co_await asio::async_connect(
            target, endpoints,
            asio::cancel_after(seconds(cfg_.dial_timeout_sec), asio::use_awaitable));
      } catch (const std::exception& e) {
        // catch 块中不允许 co_await，用同步写回失败状态
        auto f = proto::status_frame(proto::kStatusFail);
        asio::error_code wec;
        asio::write(peer, asio::buffer(f), wec);
        spdlog::info("dial target failed dst={} err={}", conn.dst, e.what());
        co_return;
      }
      target.set_option(asio::socket_base::keep_alive(true), opt_ec);

      // 3. 握手成功
      co_await proto::write_status(peer, proto::kStatusOK);

      // 4. 双向零拷贝(缓冲)转发
      std::atomic<std::int64_t> up{0}, down{0};
      auto start = steady_clock::now();
      co_await tunnel::pipe(peer, target, up, down, idle);
      spdlog::debug("conn closed user={} dst={} up={} down={} dur={}ms",
                    user, conn.dst, up.load(), down.load(),
                    duration_cast<milliseconds>(steady_clock::now() - start).count());
    } catch (const std::exception& e) {
      spdlog::debug("tunnel end: {}", e.what());
    }
  }

private:
  asio::io_context& ioc_;
  const config::ServerConfig& cfg_;
  std::atomic<int> conns_{0};
};

} // namespace

int main() {
  auto cfg = config::from_env();
  log::init(cfg.log_level);
  spdlog::info("pid={} proxy_serve starting", PROXY_GETPID());

  asio::io_context ioc;
  ProxyServer server(ioc, cfg.server);
  asio::co_spawn(ioc, server.listen(), asio::detached);

  asio::signal_set sigs(ioc, SIGINT, SIGTERM);
  sigs.async_wait([&](std::error_code, int) { ioc.stop(); });

  std::vector<std::thread> pool;
  unsigned n = std::max(2u, std::thread::hardware_concurrency());
  for (unsigned i = 1; i < n; ++i) pool.emplace_back([&] { ioc.run(); });
  ioc.run();
  for (auto& t : pool) t.join();
  return 0;
}
