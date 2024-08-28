/*
 * 代理服务器：

 * 已实现：
 *  IO复用+非阻塞IO
 *  HTTP代理
 *  HTTPS代理
 *  时间轮剔除空闲连接
 *  心跳协议
 *  用户管理(ing)
 *
 * 未实现：
 *  负载均衡
 *
 * 可选？
 *  流量监控/数据库
 *  缓存机制/redis
 *  日志记录
 *  流量控制
 *  前端
 *
 */

#include "muduo/net/TcpClient.h"
#include "muduo/net/TcpServer.h"

#include "muduo/base/Logging.h"
#include "muduo/base/Thread.h"
#include "muduo/net/EventLoop.h"
#include "muduo/net/InetAddress.h"

#include <cstddef>
#include <memory>
#include <muduo/base/AsyncLogging.h>
#include <muduo/net/TcpConnection.h>
#include <sys/types.h>
#include <utility>

#include "ConnContext.h"
#include "TimingWheel.h"
#include <codecvt>
#include <iostream>
#include <string>
#include <thread>
#include <unistd.h>

#include <boost/circular_buffer.hpp>

using namespace muduo;
using namespace muduo::net;

int num_threads = 4;

class ProxyServer {
public:
  ProxyServer(EventLoop *loop, const InetAddress &listenAddr,
              const int maxConnections = 1000000, size_t idleSeconds = 10)
      : loop_(loop), server_(loop, listenAddr, "ProxyServer"),
        maxConnections_(maxConnections), ConnectionBuckets_(idleSeconds) {
    server_.setConnectionCallback([this](const TcpConnectionPtr &conn) {
      onProxyClientConnection(conn);
    });
    server_.setMessageCallback(
        [this](const TcpConnectionPtr &client_conn, Buffer *buf,
               Timestamp time) { onMessage(client_conn, buf, time); });
    // 注册时间轮用于剔除空闲连接
    ConnectionBuckets_.resize(idleSeconds);
    loop_->runEvery(30.0, [this]() { onTimingWheel(); });
    server_.setThreadNum(num_threads);
  }

  void start() { server_.start(); }
  // void stop();

private:
  auto establishConnContext(const TcpConnectionPtr &conn) -> ConnContextPtr {
    if (!conn->getContext().empty()) {
      return boost::any_cast<std::shared_ptr<ConnContext>>(conn->getContext());
      // return nullptr;
    }
    ConnEntryPtr entry = std::make_shared<ConnEntry>(conn);
    WeakConnEntryPtr weak_entry(entry);
    // 存储弱指针为代理连接上下文
    auto client_context = std::make_shared<ConnContext>(std::move(weak_entry),
                                                        &AllConnDataFlows_);
    conn->setContext(client_context);

    // 插入时间轮末尾连接池
    {
      MutexLockGuard buckets_lock_guard(BucketLocker_);
      ConnectionBuckets_.back().insert(std::move(entry));
    }

    return client_context;
  }

  void clientConnHandle(const TcpConnectionPtr &conn) {
    numProxyConnections_.increment();
    if (numProxyConnections_.get() > maxConnections_) {
      // 达到服务器最大并发数
      // conn->send("***");
      conn->shutdown();
    }
    // LOG_INFO << " + " << conn->peerAddress().toIpPort()
    //          << " ( Concurrent connections num: " <<
    //          numProxyConnections_.get()
    //          << " ) proxy connected ";
    // establishConnContext(conn);
  }
  void clientDisConnHandle(const TcpConnectionPtr &conn) {
    // proxy客户端主动断开连接，关闭两个隧道
    // assert(!conn->getContext().empty());

    numProxyConnections_.decrement();
    // LOG_INFO << " - " << conn->peerAddress().toIpPort()
    //          << " ( Concurrent connections num: " <<
    //          numProxyConnections_.get()
    //          << " ) proxy disconnected ";

    // 目标连接为客户端连接的上下文，自动关闭
    if (!conn->getContext().empty()) {
      auto client_context =
          boost::any_cast<std::shared_ptr<ConnContext>>(conn->getContext());
      auto targetserver = client_context->getServer();
      if (targetserver) {
        auto server_conn = targetserver->connection();
        if (server_conn) {
          // server_conn->shutdown();
        }
      }
    }

    // /* 更新用户流量信息, 写入数据库？ */
    // LOG_INFO << conn->peerAddress().toIpPort()
    //          << " User data traffic has used "
    //          << client_context->getDataFlowUp() << " upload  bytes and "
    //          << client_context->getDataFlowDown() << " download  bytes";

    // // conn->shutdown();
    // // conn->forceClose();
  }
  void onProxyClientConnection(const TcpConnectionPtr &conn) {
    LOG_TRACE << conn->peerAddress().toIpPort() << " -> "
              << conn->localAddress().toIpPort() << " is "
              << (conn->connected() ? "UP" : "DOWN");

    if (conn->connected()) {
      clientConnHandle(conn);
    } else {
      clientDisConnHandle(conn);
    }

    // 账户管理/流量管理
  }

  static bool onSpecialMsg(const TcpConnectionPtr &client_conn, Buffer *buf) {
    // 特殊消息处理
    int ret = strncmp(buf->peek(), kTestMessage.c_str(), kTestMessage.length());
    // string msg(buf->peek(), kTestMessage.length());
    // if (msg == kTestMessage) {
    if (ret == 0) {
      if (buf->readableBytes() <= kTestMessage.length()) {
        buf->retrieveAll();
        // LOG_INFO << client_conn->peerAddress().toIpPort() << " TestMessage!
        // "; std::this_thread::sleep_for(std::chrono::milliseconds(1));
        // std::this_thread::sleep_for(std::chrono::microseconds(1));
        client_conn->send(kTestMessage);

        client_conn->shutdown();
        return true;
      }
    }
    string msg = string(buf->peek(), kHeartbeatMessage.length());
    if (msg == kHeartbeatMessage) {
      // 心跳包刷新时间轮，保持连接存活
      if (buf->readableBytes() <= kHeartbeatMessage.length()) {
        buf->retrieveAll();
        LOG_INFO << client_conn->peerAddress().toIpPort() << " Heart beat! ";
        return true;
      }
      // else 还有数据包
    }
    return false;
  }

  void onMessage(const TcpConnectionPtr &client_conn, Buffer *buf,
                 Timestamp time) {

    if (onSpecialMsg(client_conn, buf)) {
      return;
    }

    auto client_context = establishConnContext(client_conn);
    // auto client_context =
    //     boost::any_cast<std::shared_ptr<ConnContext>>(client_conn->getContext());

    // 时间轮刷新
    WeakConnEntryPtr weak_entry = client_context->getWeakEntry();
    ConnEntryPtr entry(weak_entry.lock());
    if (entry) {
      MutexLockGuard buckets_lock_guard(BucketLocker_);
      ConnectionBuckets_.back().insert(std::move(entry));
    }

    // if (client_conn->getContext().empty())
    if (!client_context->getServer()) {
      // 未创建创建目标服务器连接
      clientMsgWithoutTargetConn(client_conn, buf, time, client_context);

      // 多条消息，递归调用处理
      if (buf->readableBytes() > 0) {
        onMessage(client_conn, buf, time);
      }
    } else {
      auto server_conn = client_context->getServer()->connection();
      if (server_conn) {
        // 连接已建立
        client_context->increaseDataFlowUp(buf->readableBytes());
        server_conn->send(buf->retrieveAllAsString());
      }
      // else 暂未建立连接的数据异步发送
    }
  }

  void clientMsgWithoutTargetConn(const TcpConnectionPtr &client_conn,
                                  Buffer *buf, Timestamp /*time*/,
                                  ConnContextPtr &client_context) {
    InetAddress *target_addr = msgHeadHandle(client_conn, buf, client_context);
    if (target_addr == nullptr) {
      return;
    }

    // 连接目标服务器
    // client_conn->getLoop()和用户连接使用同一个工作线程Eventloop,
    // 直接使用loop_使用的是main函数的Eventloop, 业务部分应该在线程池处理
    auto target_server = std::make_shared<TcpClient>(
        client_conn->getLoop(), *target_addr, "targetServer");

    // 回调函数持有其弱指针, 强指针会导致循环引用，无法析构
    std::weak_ptr<TcpConnection> weak_client_conn(client_conn);
    // 设置目标主机回调函数
    target_server->setConnectionCallback(
        [this, weak_client_conn](const TcpConnectionPtr &server_conn) {
          targetConnHandle(weak_client_conn, server_conn);
        });
    target_server->setMessageCallback(
        [weak_client_conn](const TcpConnectionPtr &server_conn, Buffer *buf,
                            Timestamp tmp) {
          targetMsgHandle(weak_client_conn, server_conn, buf, tmp);
        });
    target_server->connect();

    // 存储目标主机的 TcpClient 指针
    client_context->setServer(target_server);

    if (target_addr->port() == 443) {
      // HTTPS请求，响应客户端 CONNECT 成功
      client_conn->send("HTTP/1.1 200 Connection Established\r\n\r\n");
    }
    // HTTP请求，忽略客户端请求头

    delete target_addr;
  }

  void targetConnHandle(const std::weak_ptr<TcpConnection> &weak_client_conn,
                        const TcpConnectionPtr &server_conn) {
    // 取出其强引用指针
    auto shared_client_conn = weak_client_conn.lock();
    if (server_conn->connected()) {
      numTargetConnections_.increment();
      LOG_INFO << " * " << server_conn->peerAddress().toIpPort()
               << " ( Concurrent connections num: "
               << numTargetConnections_.get() << " ) target server connected ";

      // 此时连接已经建立，发送clientConn缓存数据
      if (shared_client_conn) {
        // 代理客户端连接存活
        Buffer *send_cache = shared_client_conn->inputBuffer();
        if (send_cache->readableBytes() > 0) {
          // 获取上下文, 统计数据流量
          auto shared_client_context =
              boost::any_cast<std::shared_ptr<ConnContext>>(
                  shared_client_conn->getContext());
          shared_client_context->increaseDataFlowUp(
              send_cache->readableBytes());
          server_conn->send(send_cache->retrieveAllAsString());
        }
      } else {
        // 代理客户端连接死亡
        // server_conn->shutdown();
      }
    } else {
      // 目标服务器主动断开连接，关闭两个隧道
      numTargetConnections_.decrement();
      LOG_INFO << " # " << server_conn->peerAddress().toIpPort()
               << " ( Concurrent connections num: "
               << numTargetConnections_.get()
               << " ) target server disconnected ";

      // server_conn->shutdown();
      // server_conn->forceClose();

      if (shared_client_conn) {
        // 代理客户端连接存活，断开
        /* 冗余？ */
        // auto sharedClientContext =
        // boost::any_cast<std::shared_ptr<ConnContext>>(sharedClientConn->getContext());
        // LOG_INFO << sharedClientConn->peerAddress().toIpPort()
        // << " User data traffic has used "
        // << sharedClientContext->getDataFlowUp() << " upload  bytes
        // and "
        // << sharedClientContext->getDataFlowDown() << " download
        // bytes";

        // shared_client_conn->shutdown();
      }
      // 代理客户端连接死亡，无操作
    }
  }

  static void
  targetMsgHandle(const std::weak_ptr<TcpConnection> &weak_client_conn,
                  const TcpConnectionPtr & /*server_conn*/, Buffer *buf,
                  Timestamp /*unused*/) {
    auto shared_client_conn = weak_client_conn.lock();
    if (shared_client_conn) {
      // 代理客户端连接存活
      auto shared_client_context =
          boost::any_cast<std::shared_ptr<ConnContext>>(
              shared_client_conn->getContext());
      shared_client_context->increaseDataFlowDown(buf->readableBytes());
      shared_client_conn->send(buf->retrieveAllAsString());
    } else {
      // 代理客户端连接死亡
      // server_conn->shutdown();
    }
  }

  static InetAddress *msgHeadHandle(const TcpConnectionPtr &client_conn,
                                    Buffer *buf,
                                    ConnContextPtr &client_context) {
    string data(buf->peek(), buf->readableBytes());
    // 查找消息边界
    size_t msg_end_pos = data.find("\r\n\r\n");
    if (msg_end_pos == std::string::npos) {
      // 不完整消息，等待下次消息到来触发回调
      return nullptr;
    }

    // 取出完整消息头
    string msg = buf->retrieveAsString(msg_end_pos + 4);
    // string msg = buf->retrieveAllAsString();

    // 默认为 CONNECT 请求
    // 解析 CONNECT 请求，获取目标主机和端口/用户信息
    string target_serve_ip;
    uint16_t target_serve_port;
    string user_name;

    // 解析 CONNECT 请求，获取目标主机和端口
    size_t host_pos = msg.find("Host:");
    if (host_pos != std::string::npos) {
      size_t start_pos = host_pos + 6; // "Host: "的长度
      size_t end_pos = msg.find("\r\n", start_pos);
      std::string host_field_value = msg.substr(start_pos, end_pos - start_pos);

      // 如果Host字段的值包含端口信息，分割主机和端口
      size_t colon_pos = host_field_value.find(':');
      std::string host;
      std::string port;
      if (colon_pos != std::string::npos) {
        target_serve_ip = host_field_value.substr(0, colon_pos);
        target_serve_port = stoi(host_field_value.substr(colon_pos + 1));
      } else {
        target_serve_ip = host_field_value;
        target_serve_port = 80;
      }
    } else {
      LOG_ERROR << client_conn->peerAddress().toIpPort()
                << " get host:port fail, disconnected! ";
      // client_conn->shutdown();
    }

    // 获取用户信息
    size_t user_pos = msg.find("User:");
    if (user_pos != std::string::npos) {
      size_t start_pos = user_pos + 6; // "User: "的长度
      size_t end_pos = msg.find("\r\n", start_pos);
      user_name = msg.substr(start_pos, end_pos - start_pos);
    } else {
      LOG_ERROR << client_conn->peerAddress().toIpPort()
                << " get userinf fail, disconnected! ";
      // client_conn->shutdown();
    }
    client_context->setUserName(user_name);

    // 使用DNS解析获取IP地址
    auto *target_addr = new InetAddress(target_serve_port);
    if (!InetAddress::resolve(target_serve_ip, target_addr)) {
      LOG_ERROR << "DNS resolution failure!!!";
      // client_conn->shutdown();
      return nullptr;
    }
    return target_addr;
  }

  void onTimingWheel() {
    // 心跳协议
    // 倒数第二个元素连接池
    Bucket &second_bucket = ConnectionBuckets_.at(1);
    for (const auto &conn_ptr : second_bucket) {
      auto weak_entry = conn_ptr->getWeakConn();
      auto strong_entry = weak_entry.lock();
      if (strong_entry) {
        // 发起心跳
        strong_entry->send(kHeartbeatMessage);
      }
    }

    // 时间轮刷新
    {
      MutexLockGuard buckets_lock_guard(BucketLocker_);
      ConnectionBuckets_.push_back(Bucket());
    }
  }

  EventLoop *loop_;
  TcpServer server_;
  muduo::AtomicInt32 numProxyConnections_;
  muduo::AtomicInt32 numTargetConnections_;
  const int maxConnections_;

  BucketQueue ConnectionBuckets_;
  MutexLock BucketLocker_;

  // 流量统计。。。
  ConnDataFlowsMap AllConnDataFlows_;
};

off_t k_roll_size = static_cast<off_t>(1024 * 1024 * 512);
AsyncLogging *g_async_log =
    new AsyncLogging(::basename("proxy_sever_"), k_roll_size);

int main(int argc, char *argv[]) {
  LOG_INFO << "pid = " << getpid() << ", tid = " << CurrentThread::tid();
  LOG_INFO << "sizeof TcpConnection = " << sizeof(TcpConnection);

  g_async_log->start();
  auto async_output = [](const char *msg, int len) -> void {
    g_async_log->append(msg, len);
  };
  Logger::setOutput(async_output);

  if (argc > 1) {
    num_threads = atoi(argv[1]);
  }
  bool ipv6 = argc > 2;
  EventLoop loop;
  InetAddress listen_addr(23456, false, ipv6);
  ProxyServer proxy_server(&loop, listen_addr);

  proxy_server.start();
  loop.loop();
}

/*
 * bug：
 *  1. 20231123 09:00:56.558011Z  8552 WARN  fd = 77 Channel::handle_event()
 * POLLHUP - Channel.cc:91 20231123 09:00:56.558047Z  8552 ERROR
 * Connector::handleError state=1 - Connector.cc:199 20231123 09:00:56.558071Z
 * 8552 INFO  Connector::retry - Retry connecting to 150.138.125.58:443 in 8000
 * milliseconds.  - Connector.cc:215 打开b站视频时发生，对端断开连接，尝试重连?
 *  2. 20231123 09:00:41.769064Z  8562 ERROR TcpConnection::handleError
 * [ProxyServer-0.0.0.0:23456#72] - SO_ERROR = 32 Broken pipe -
 * TcpConnection.cc:426 管道破裂，原因未知
 *  3. 20231123 07:59:10.658948Z 28879 ERROR TcpConnection::handleError
 * [targetServer:104.46.162.226:443#1] - SO_ERROR = 104 Connection reset by peer
 * - TcpConnection.cc:426 连接复位，原因未知
 *
 *  其他暂无
 *
 */

// g++ proxy_serve.cc -lmuduo_net -lmuduo_base -lpthread -std=c++11 -o
// proxy_serve
