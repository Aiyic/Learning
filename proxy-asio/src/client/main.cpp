// proxy_client：接入层。面向用户监听 HTTP/HTTPS 代理，鉴权并解析目标后，
// 通过内部隧道协议把流量转给上游 proxy_serve。每连接一个协程 + 独立 strand。
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
#include "proxy/proxy.hpp"
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

struct ConnGuard {
  std::atomic<int>& c;
  ~ConnGuard() { c.fetch_sub(1); }
};

class ProxyClient {
public:
  ProxyClient(asio::io_context& ioc, const config::ClientConfig& cfg)
      : ioc_(ioc), cfg_(cfg), authn_(cfg.users) {}

  awaitable<void> listen(std::string addr, bool is_https) {
    tcp::acceptor acc(ioc_, net::make_endpoint(ioc_, addr));
    acc.set_option(asio::socket_base::reuse_address(true));
    spdlog::info("proxy_client listening on {} ({}) upstream={}", addr,
                 is_https ? "HTTPS" : "HTTP", cfg_.server_addr);

    while (true) {
      auto strand = asio::make_strand(ioc_);
      tcp::socket peer(strand);
      std::error_code ec;
      co_await acc.async_accept(peer,
                                asio::redirect_error(asio::use_awaitable, ec));
      if (ec) {
        if (ioc_.stopped()) co_return;
        continue;
      }
      if (conns_.fetch_add(1) + 1 > cfg_.max_conns) {
        conns_.fetch_sub(1);
        peer.close();
        continue;
      }
      asio::co_spawn(strand, handle_client(std::move(peer), is_https),
                     asio::detached);
    }
  }

  awaitable<void> handle_client(tcp::socket user, bool /*is_https*/) {
    ConnGuard guard{conns_};
    auto exec = co_await asio::this_coro::executor;
    seconds idle(cfg_.idle_timeout_sec);

    asio::error_code opt_ec;
    user.set_option(asio::socket_base::keep_alive(true), opt_ec);

    try {
      // 1. 读请求头(async 版 bufio 读到分隔符)
      asio::streambuf buf;
      std::size_t n = co_await asio::async_read_until(
          user, buf, "\r\n\r\n",
          asio::cancel_after(seconds(cfg_.dial_timeout_sec), asio::use_awaitable));
      std::string head(n, '\0');
      asio::buffer_copy(asio::buffer(head), buf.data(), n);
      buf.consume(n);

      auto req = proxyx::parse_request(head);
      if (!req) co_return;

      // 2. 鉴权
      auto user_id = authn_.authenticate(req->auth_header);
      if (!user_id) {
        auto resp = proxyx::auth_required_response("proxy");
        co_await asio::async_write(user, asio::buffer(resp), asio::use_awaitable);
        co_return;
      }
      std::string uid = *user_id;

      // 3. 拨号上游 proxy_serve
      tcp::socket tunnel(exec);
      try {
        auto endpoints = co_await net::resolve(cfg_.server_addr);
        co_await asio::async_connect(
            tunnel, endpoints,
            asio::cancel_after(seconds(cfg_.dial_timeout_sec), asio::use_awaitable));
      } catch (...) {
        if (req->is_connect) {
          auto resp = proxyx::bad_gateway_response();
          asio::error_code ig;
          asio::write(user, asio::buffer(resp), ig);
        }
        co_return;
      }
      tunnel.set_option(asio::socket_base::keep_alive(true), opt_ec);

      // 4. 隧道握手
      co_await proto::write_connect(tunnel, proto::Connect{uid, req->target});
      auto status = co_await proto::read_status(tunnel);
      if (status != proto::kStatusOK) {
        if (req->is_connect) {
          auto resp = proxyx::bad_gateway_response();
          co_await asio::async_write(user, asio::buffer(resp), asio::use_awaitable);
        }
        co_return;
      }

      // 5. 协议收尾
      if (req->is_connect) {
        auto resp = proxyx::connect_ok_response();
        co_await asio::async_write(user, asio::buffer(resp), asio::use_awaitable);
      } else {
        co_await asio::async_write(tunnel, asio::buffer(req->forward_head),
                                   asio::use_awaitable);
      }
      // 把 bufio 中残留字节(请求体 / 流水线 TLS 握手)转发给上游
      if (buf.size() > 0) {
        co_await asio::async_write(tunnel, buf.data(), asio::use_awaitable);
        buf.consume(buf.size());
      }

      // 6. 双向转发
      std::atomic<std::int64_t> up{0}, down{0};
      co_await tunnel::pipe(user, tunnel, up, down, idle);
    } catch (const std::exception& e) {
      spdlog::debug("client conn end: {}", e.what());
    }
  }

private:
  asio::io_context& ioc_;
  const config::ClientConfig& cfg_;
  auth::Authenticator authn_;
  std::atomic<int> conns_{0};
};

} // namespace

int main() {
  auto cfg = config::from_env();
  log::init(cfg.log_level);
  spdlog::info("pid={} proxy_client starting auth={}", PROXY_GETPID(),
               cfg.client.users.empty() ? "off" : "on");

  asio::io_context ioc;
  ProxyClient client(ioc, cfg.client);
  asio::co_spawn(ioc, client.listen(cfg.client.https_addr, true), asio::detached);
  asio::co_spawn(ioc, client.listen(cfg.client.http_addr, false), asio::detached);

  asio::signal_set sigs(ioc, SIGINT, SIGTERM);
  sigs.async_wait([&](std::error_code, int) { ioc.stop(); });

  std::vector<std::thread> pool;
  unsigned n = std::max(2u, std::thread::hardware_concurrency());
  for (unsigned i = 1; i < n; ++i) pool.emplace_back([&] { ioc.run(); });
  ioc.run();
  for (auto& t : pool) t.join();
  return 0;
}
