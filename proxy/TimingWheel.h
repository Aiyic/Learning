
#ifndef MUDUO_NET_TIMINGWHEEL_H
#define MUDUO_NET_TIMINGWHEEL_H

#include "muduo/net/TcpClient.h"
#include "muduo/net/TcpConnection.h"
#include <boost/circular_buffer.hpp>
#include <memory>
#include <muduo/base/Logging.h>
#include <unordered_set>
#include <utility>

namespace muduo {
namespace net {

class ConnEntry;
using WeakTcpConnectionPtr = std::weak_ptr<muduo::net::TcpConnection>;
using ConnEntryPtr = std::shared_ptr<ConnEntry>;
using WeakConnEntryPtr = std::weak_ptr<ConnEntry>;
using Bucket = std::unordered_set<ConnEntryPtr>;
using BucketQueue = boost::circular_buffer<Bucket>;

class ConnEntry : copyable {
public:
  explicit ConnEntry(WeakTcpConnectionPtr weakConn)
      : weakConn_(std::move(weakConn)) {}

  ~ConnEntry() {
    TcpConnectionPtr conn = weakConn_.lock();
    if (conn) {
      conn->shutdown();
      // LOG_INFO << conn->peerAddress().toIpPort() << " timeout shutdown!";
    } else {
      // LOG_INFO << "proxy conn already destoryed!";
    }
  }
  const WeakTcpConnectionPtr &getWeakConn() const { return weakConn_; }

private:
  WeakTcpConnectionPtr weakConn_;
};

} // namespace net
} // namespace muduo

#endif // MUDUO_NET_TIMINGWHEEL_H
