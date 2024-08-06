#include "muduo/base/Logging.h"
#include "muduo/base/Thread.h"
#include "muduo/net/EventLoop.h"
#include "muduo/net/InetAddress.h"
#include "muduo/net/TcpClient.h"
#include "muduo/net/TcpServer.h"

#include <functional>
#include <muduo/base/AsyncLogging.h>

#include "ConnContext.h"
#include <iostream>
#include <muduo/net/Callbacks.h>
#include <unistd.h>
#include <utility>

using namespace muduo;
using namespace muduo::net;

const char *proxy_serve_host = "127.0.0.1";
const uint16_t kProxyServePort = 23456; // 服务器端口

int num_threads = 0;

class ProxyClient : noncopyable {
public:
  ProxyClient(EventLoop *loop, const InetAddress &listenAddr, bool isHTTPS,
              const int maxConnections = 1000000)
      : loop_(loop), client_(loop, listenAddr, "ProxyClient"),
        isHTTPS_(isHTTPS), maxConnections_(maxConnections) {
    // client_.setConnectionCallback(
    //     std::bind(&ProxyClient::onUserConnection, this, _1));
    // client_.setMessageCallback(
    //     std::bind(&ProxyClient::onMessage, this, _1, _2, _3));
    client_.setConnectionCallback(
        [this](const TcpConnectionPtr &conn) { onUserConnection(conn); });
    client_.setMessageCallback(
        [this](const TcpConnectionPtr &clientConn, Buffer *buf,
               Timestamp time) { onMessage(clientConn, buf, time); });
    client_.setThreadNum(num_threads);
  }

  void start() { client_.start(); }
  // void stop();

private:
  void onUserConnection(const TcpConnectionPtr &clientConn) {
    LOG_TRACE << clientConn->localAddress().toIpPort() << " -> "
              << clientConn->peerAddress().toIpPort() << " is "
              << (clientConn->connected() ? "UP" : "DOWN");
    if (clientConn->connected()) {
      userConnHandle(clientConn);
    } else {
      userDisConnHandle(clientConn);
    }
  }

  void userConnHandle(const TcpConnectionPtr &clientConn) {
    numUserConnections_.increment();
    if (numUserConnections_.get() > maxConnections_) {
      // 达到服务器最大并发数
      clientConn->shutdown();
    }

    LOG_INFO << clientConn->peerAddress().toIpPort()
             << " ( Concurrent connections num: " << numUserConnections_.get()
             << " ) user connected ";

    if (clientConn->getContext().empty()) {
      // 未连接代理服务器

      /* 控制负载均衡 */
      // clientConn->getLoop()和用户连接使用同一个工作线程Eventloop,
      // 直接使用loop_使用的是main函数的Eventloop, 业务部分应该在线程池处理
      // auto proxyServer = std::make_shared<TcpClient>(loop_,
      // InetAddress(PROXY_SERVE_HOST, PROXY_SERVE_PORT), "ServerClient");
      auto proxy_server = std::make_shared<TcpClient>(
          clientConn->getLoop(), InetAddress(proxy_serve_host, kProxyServePort),
          "ServerClient");

      // 回调函数持有其弱指针, 强指针会导致循环引用，无法析构
      std::weak_ptr<TcpConnection> weak_client_conn(clientConn);

      // 设置代理服务器连接回调
      proxy_server->setConnectionCallback(
          [this, &weak_client_conn](const TcpConnectionPtr &server_conn) {
            serverConnHandle(weak_client_conn, server_conn);
          });

      // 设置代理服务器读事件回调
      proxy_server->setMessageCallback(
          [&weak_client_conn](const TcpConnectionPtr &server_conn,
                                    Buffer *buf, Timestamp tmp) {
            serverMsgHandle(weak_client_conn, server_conn, buf, tmp);
          });

      proxy_server->connect();

      // 用户连接持有代理服务器连接
      // 代理客户端不主动断开用户连接
      auto client_context =
          std::make_shared<ConnContext>(std::move(proxy_server));
      auto user_ip = clientConn->peerAddress().toIp();
      // if(userIp == "127.0.0.1")
      //   userIp = selfAddr_.toIp();
      //   getLocalAddr(clientConn.fd()).toIp();

      client_context->setUserName(user_ip);
      clientConn->setContext(client_context);
    }
  }

  void userDisConnHandle(const TcpConnectionPtr &clientConn) {
    // 用户主动断开连接，关闭隧道和用户连接
    assert(!clientConn->getContext().empty());

    numUserConnections_.decrement();
    LOG_INFO << clientConn->peerAddress().toIpPort()
             << " ( Concurrent connections num: " << numUserConnections_.get()
             << " ) user disconnected ";

    // 代理服务器连接为用户连接的上下文，自动关闭
    auto client_context =
        boost::any_cast<std::shared_ptr<ConnContext>>(clientConn->getContext());
    auto proxy_server = client_context->getServer();
    if (proxy_server) {
      auto server_conn = proxy_server->connection();
      if (server_conn) {
        server_conn->shutdown();
      }
    }
    clientConn->shutdown();
    // clientConn->forceClose();
  }

  void serverConnHandle(std::weak_ptr<TcpConnection> &weak_client_conn,
                        const TcpConnectionPtr &server_conn) {
    auto shared_client_conn = weak_client_conn.lock();
    if (server_conn->connected()) {
      numServerConnections_.increment();
      LOG_INFO << server_conn->peerAddress().toIpPort()
               << " ( Concurrent connections num: "
               << numServerConnections_.get() << " ) proxy server connected ";

      // 连接已经建立，发送用户连接缓存数据
      if (shared_client_conn) {
        // 用户连接存活, 获取上下文
        auto client_context = boost::any_cast<std::shared_ptr<ConnContext>>(
            shared_client_conn->getContext());

        if (shared_client_conn->inputBuffer()->readableBytes() > 0) {
          // 用户连接缓冲区存在数据
          // server_conn->send(sharedClientConn->inputBuffer()->retrieveAllAsString());
          string msg(shared_client_conn->inputBuffer()->retrieveAllAsString());
          clientMsgHandle(server_conn, shared_client_conn, client_context, msg);
        }
      }
    } else {
      // 代理服务器主动断开连接，关闭隧道和用户连接
      numServerConnections_.decrement();
      LOG_INFO << server_conn->peerAddress().toIpPort()
               << " ( Concurrent connections num: "
               << numServerConnections_.get()
               << " ) proxy server disconnected ";

      server_conn->shutdown();
      // server_conn->forceClose();

      if (shared_client_conn) {
        // 用户连接存活，断开
        shared_client_conn->shutdown();
      }
      // 用户连接死亡，无操作
    }
  }

  static void serverMsgHandle(std::weak_ptr<TcpConnection> &weak_client_conn,
                              const TcpConnectionPtr &server_conn, Buffer *buf,
                              Timestamp /*unused*/) {
    auto shared_client_conn = weak_client_conn.lock();
    if (shared_client_conn) {
      // 用户连接存活
      string msg(buf->retrieveAllAsString());
      if (msg == kTestMessage) {
        auto client_context = boost::any_cast<std::shared_ptr<ConnContext>>(
            shared_client_conn->getContext());
        if (client_context->isTestNumsEmpty()) {
          shared_client_conn->send("kTestMessage");
          shared_client_conn->shutdown();
          LOG_INFO << shared_client_conn->peerAddress().toIpPort()
                   << " kTestMessage over! Send pkg num:"
                   << kTestNums - client_context->getTestNums();

        } else {
          server_conn->send(kTestMessage);
          client_context->decTestNums();
          // LOG_INFO << shared_client_conn->peerAddress().toIpPort()
          //         << " kTestMessage! ";
        }
      } else if (msg == kHeartbeatMessage) {
        // 心跳包返回给代理服务器，保持连接存活
        server_conn->send(kHeartbeatMessage);
        LOG_INFO << shared_client_conn->peerAddress().toIpPort()
                 << " Heart beat! ";
      } else {
        // 消息包返回给用户连接
        shared_client_conn->send(msg);
      }
    } else {
      // 用户连接死亡
      server_conn->shutdown();
    }
  }

  void onMessage(const TcpConnectionPtr &clientConn, Buffer *buf,
                 Timestamp /*unused*/) const {
    auto client_context =
        boost::any_cast<std::shared_ptr<ConnContext>>(clientConn->getContext());
    auto server_conn = client_context->getServer()->connection();

    if (server_conn) {
      // 连接已建立
      string msg(buf->retrieveAllAsString());
      clientMsgHandle(server_conn, clientConn, client_context, msg);
    }
    // else 暂未建立连接的数据异步发送
  }

  void clientMsgHandle(const TcpConnectionPtr &server_conn,
                       const TcpConnectionPtr &clientConn,
                       ConnContextPtr &client_context, string &msg) const {
    if (msg == kTestMessage) {
      // 测试连接消息
      // (echo 'test'; sleep 2) | telnet 127.0.0.1 12345
      server_conn->send(msg);
      client_context->setTestNums();
      LOG_INFO << clientConn->peerAddress().toIpPort() << " kTestMessage! ";
    } else {
      if (!client_context->getConnectState()) {
        // 构造代理请求头, 加入用户信息
        string head = constructProxyHead(client_context, msg);

        // HTTPS 用户信息直接加入CONNECT请求 (原生CONNECT请求包含主机端口)
        // HTTP 以第一个访问请求加入用户信息作为类CONNECT请求
        // (HTTP请求包含主机端口)
        server_conn->send(head);
        if (!isHTTPS_) {
          // HTTP 发送真实请求
          server_conn->send(msg);
        }

      } else {
        // 代理头已发送，发送请求正文
        server_conn->send(msg);
      }
    }
  }

  static string
  constructProxyHead(const std::shared_ptr<ConnContext> &connContext,
                     const string &msg) {
    string head(msg, 0, msg.length() - 2);
    head = head + "User: " + connContext->getUserName() + "\r\n\r\n";
    // 设置CONNECT请求已建立
    connContext->setConnectState();
    return head;
  }

  EventLoop *loop_;
  TcpServer client_;
  InetAddress selfAddr_ = InetAddress(0);
  muduo::AtomicInt32 numUserConnections_;
  muduo::AtomicInt32 numServerConnections_;
  const bool isHTTPS_;
  const int maxConnections_;
};

off_t k_roll_size = static_cast<off_t>(1024 * 1024 * 512);
AsyncLogging *g_async_log =
    new AsyncLogging(::basename("proxy_client_"), k_roll_size);

int main(int argc, char * /*argv*/[]) {
  LOG_INFO << "pid = " << getpid() << ", tid = " << CurrentThread::tid();

  g_async_log->start();
  auto async_output = [](const char *msg, int len) -> void {
    g_async_log->append(msg, len);
  };
  Logger::setOutput(async_output);

  EventLoop loop;
  bool ipv6 = argc > 3;
  InetAddress https_proxy_addr(12345, false, ipv6);
  ProxyClient https_proxy_client_serve(&loop, https_proxy_addr, true);
  InetAddress http_proxy_addr(12346, false, ipv6);
  ProxyClient http_proxy_client_serve(&loop, http_proxy_addr, false);

  https_proxy_client_serve.start();
  http_proxy_client_serve.start();
  loop.loop();
}

// export https_proxy="http://127.0.0.1:12345"
// export http_proxy="http://127.0.0.1:12346"
// g++ proxy_client.cc -lmuduo_net -lmuduo_base -lpthread -std=c++11 -o
// proxy_client
