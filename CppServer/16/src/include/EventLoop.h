/**
 * @file EventLoop.h
 * @author 冯岳松 (yuesong-feng@foxmail.com)
 * @brief
 * @version 0.1
 * @date 2022-01-04
 *
 * @copyright Copyright (冯岳松) 2022
 *
 */
#pragma once
#include <memory>
#include <sys/eventfd.h>
#include "common.h"

class EventLoop {
 public:
  DISALLOW_COPY_AND_MOVE(EventLoop);
  EventLoop();
  ~EventLoop();

  void Loop();
  void UpdateChannel(Channel *ch) const;
  void DeleteChannel(Channel *ch) const;

  void ExitLoop();

 private:
  std::unique_ptr<Poller> poller_;
  std::unique_ptr<Channel> exit_channel;

  static int GetExitEventFd();
};
