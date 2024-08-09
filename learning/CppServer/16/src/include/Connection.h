/**
 * @file Connection.h
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
#include <string>
#include "common.h"

class Connection {
 public:
  enum State {
    Invalid = 0,
    Connecting,
    Connected,
    Closed,
  };
  DISALLOW_COPY_AND_MOVE(Connection);
  Connection(int fd, EventLoop *loop);
  ~Connection();

  void SetDeleteConnection(std::function<void(int)> const &fn);
  void SetOnConnect(std::function<void(Connection *)> const &fn);
  void SetOnRecv(std::function<void(Connection *)> const &fn);
  [[nodiscard]] State GetState() const;
  [[nodiscard]] Socket *GetSocket() const;
  void SetSendBuf(const char *str);
  Buffer *ReadBuf();
  Buffer *SendBuf();

  RC Read();
  RC Write();
  RC Send(std::string const &msg);

  void Close();

  void OnConnect(std::function<void()> fn);
  void OnMessage(std::function<void()> fn);

 private:
  void Business();
  RC ReadNonBlocking();
  RC WriteNonBlocking();
  RC ReadBlocking();
  RC WriteBlocking();

  std::unique_ptr<Socket> socket_;
  std::unique_ptr<Channel> channel_;

  State state_;
  std::unique_ptr<Buffer> read_buf_;
  std::unique_ptr<Buffer> send_buf_;

  std::function<void(int)> delete_connectioin_;
  std::function<void(Connection *)> on_recv_;
};
