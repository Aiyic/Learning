/**
 * @file Acceptor.h
 * @author 冯岳松 (yuesong-feng@foxmail.com)
 * @brief
 * @version 0.1
 * @date 2022-01-04
 *
 * @copyright Copyright (冯岳松) 2022
 *
 */
#pragma once
#include <functional>
#include <memory>
#include "common.h"

class Acceptor {
 public:
  DISALLOW_COPY_AND_MOVE(Acceptor);
  explicit Acceptor(EventLoop *loop);
  ~Acceptor();

  [[nodiscard]] RC AcceptConnection() const;
  void SetNewConnectionCallback(std::function<void(int)> const &callback);

 private:
  std::unique_ptr<Socket> socket_;
  std::unique_ptr<Channel> channel_;
  std::function<void(int)> new_connection_callback_;
};
