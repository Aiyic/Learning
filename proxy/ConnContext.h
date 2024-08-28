
#ifndef MUDUO_NET_CONNCONTEXT_H
#define MUDUO_NET_CONNCONTEXT_H

#include "TimingWheel.h"
#include "muduo/base/noncopyable.h"
#include "muduo/net/TcpClient.h"
#include <memory>
#include <unordered_map>
#include <utility>

namespace muduo {
namespace net {

// 心跳包规则
const std::string kHeartbeatMessage = "Heartbeat\r\n";
const std::string kTestMessage = "GET / HTTP/1.0\r\nHost: localhost:23456\r\nUser-Agent: ApacheBench/2.3\r\nAccept: */*\r\n\r\n";
const int kTestNums = 1;

class ConnContext;
using ConnContextPtr = std::shared_ptr<muduo::net::ConnContext>;
using TcpClientPtr = std::shared_ptr<muduo::net::TcpClient>;
using ConnDataFlowsMap =
    std::unordered_map<std::string, std::pair<size_t, size_t>>;

class ConnContext : noncopyable {
public:
  explicit ConnContext(TcpClientPtr &Server) : Server_(Server) {}
  explicit ConnContext(TcpClientPtr &&Server) : Server_(std::move(Server)) {}

  ConnContext(WeakConnEntryPtr&& weakEntry, ConnDataFlowsMap *AllConnDataFlows)
      : Server_(nullptr), weakEntry_(std::move(weakEntry)),
        AllConnDataFlows_(AllConnDataFlows) {}

  ConnContext(ConnContext&& other) noexcept
    : Server_(std::move(other.Server_)),
      weakEntry_(std::move(other.weakEntry_)),
      Connected_(other.Connected_),
      username_(std::move(other.username_)),
      dataFlowUp_(other.dataFlowUp_),
      dataFlowDown_(other.dataFlowDown_),
      totalDataFlowUp_(other.totalDataFlowUp_),
      totalDataFlowDown_(other.totalDataFlowDown_),
      AllConnDataFlows_(other.AllConnDataFlows_),
      test_num_(other.test_num_) {
    other.dataFlowUp_ = 0;
    other.dataFlowDown_ = 0;
    other.totalDataFlowUp_ = 0;
    other.totalDataFlowDown_ = 0;
    other.AllConnDataFlows_ = nullptr;
    other.test_num_ = 0;
  }

  ~ConnContext() {
    // assert(dataFlowUp_==0);
    // assert(dataFlowDown_==0);’
    if (AllConnDataFlows_ != nullptr) {
      if (AllConnDataFlows_->count(username_) != 0U) {
        auto &conn_data_flows = (*AllConnDataFlows_)[username_];
        conn_data_flows.first += totalDataFlowUp_;
        conn_data_flows.second += totalDataFlowDown_;
      } else {
        (*AllConnDataFlows_)[username_] =
            std::pair<size_t, size_t>(totalDataFlowUp_, totalDataFlowDown_);
      }
    }
  }

  const TcpClientPtr &getServer() const { return Server_; }
  void setServer(const TcpClientPtr &Server) { Server_ = Server; }

  const WeakConnEntryPtr &getWeakEntry() const { return weakEntry_; }

  void setConnectState() { Connected_ = true; }
  bool getConnectState() const { return Connected_; }
  
  void setTestNums() { test_num_ = kTestNums; }
  int getTestNums() const { return test_num_ ; }
  void decTestNums() { --test_num_; }
  bool isTestNumsEmpty() const { return test_num_<=0; }

  const string &getUserName() const { return username_; }
  void setUserName(const string &userName) { username_ = userName; }

  void increaseDataFlowUp(const size_t &flow) { dataFlowUp_ += flow; }
  void increaseDataFlowDown(const size_t &flow) { dataFlowDown_ += flow; }
  size_t getDataFlowUp() {
    size_t tmp = dataFlowUp_;
    totalDataFlowUp_ += dataFlowUp_;
    dataFlowUp_ = 0;
    return tmp;
  }
  size_t getDataFlowDown() {
    size_t tmp = dataFlowDown_;
    totalDataFlowDown_ += dataFlowDown_;
    dataFlowDown_ = 0;
    return tmp;
  }

private:
  TcpClientPtr Server_;
  WeakConnEntryPtr weakEntry_;

  // 仅 HTTP 请求使用
  bool Connected_ = false;

  string username_;
  size_t dataFlowUp_ = 0;
  size_t dataFlowDown_ = 0;
  size_t totalDataFlowUp_ = 0;
  size_t totalDataFlowDown_ = 0;

  ConnDataFlowsMap *AllConnDataFlows_ = nullptr;

  int test_num_;
};

} // namespace net
} // namespace muduo

#endif // MUDUO_NET_CONNCONTEXT_H
