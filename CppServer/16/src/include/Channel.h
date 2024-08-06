/**
 * @file Channel.h
 * @author 冯岳松 (yuesong-feng@foxmail.com)
 * @brief
 * @version 0.1
 * @date 2022-01-04
 *
 * @copyright Copyright (冯岳松) 2022
 *
 */
#pragma once
#include <cstdint>
#include <functional>
#include "common.h"

class Channel {
 public:
  DISALLOW_COPY_AND_MOVE(Channel);
  Channel(int fd, EventLoop *loop);
  ~Channel();

  void HandleEvent() const;
  void EnableRead();
  void EnableWrite();

  [[nodiscard]] int GetFd() const;
  [[nodiscard]] uint32_t ListenEvents() const;
  [[nodiscard]] uint32_t ReadyEvents() const;
  [[nodiscard]] bool Exist() const;
  void SetExist(bool in = true);
  void EnableET();

  void SetReadyEvent(uint32_t ev);
  void SetReadCallback(std::function<void()> const &callback);
  void SetWriteCallback(std::function<void()> const &callback);

  static const int8_t READ_EVENT;
  static const int8_t WRITE_EVENT;
  static const int8_t ET;

 private:
  int fd_;
  EventLoop *loop_;
  uint32_t listen_events_;
  uint32_t ready_events_;
  bool exist_;
  std::function<void()> read_callback_;
  std::function<void()> write_callback_;
};
