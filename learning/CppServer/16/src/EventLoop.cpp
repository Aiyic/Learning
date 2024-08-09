/**
 * @file EventLoop.cpp
 * @author 冯岳松 (yuesong-feng@foxmail.com)
 * @brief
 * @version 0.1
 * @date 2022-01-04
 *
 * @copyright Copyright (冯岳松) 2022
 *
 */
#include "EventLoop.h"
#include <iostream>
#include <vector>
#include <unistd.h>
#include "Channel.h"
#include "Poller.h"
#include "common.h"
#include "Exception.h"

EventLoop::EventLoop() { 
  poller_ = std::make_unique<Poller>(); 

  exit_channel = std::make_unique<Channel>(GetExitEventFd(), this);
  exit_channel->EnableRead();
  exit_channel->EnableET();
  std::function<void()> ext = std::bind([](){ throw Exception(ExceptionType::EXIT_EVENT_LOOP, "event loop exit"); });
  exit_channel->SetReadCallback(ext);
  
}

EventLoop::~EventLoop() = default;

int EventLoop::GetExitEventFd() {
  static int event_fd = eventfd(0, EFD_CLOEXEC); // 静态对象，在首次调用时初始化
  return event_fd;
}

void EventLoop::ExitLoop() {
  uint64_t event_value = 1;  // 使用非零值表示事件
  ssize_t n = write(GetExitEventFd(), &event_value, sizeof(event_value));
  ErrorIf(n == -1, "event write error");
}

void EventLoop::Loop() {
  while (true) {
    for (Channel *active_ch : poller_->Poll()) {
      try{
        active_ch->HandleEvent();
      }
      catch(const Exception& e ){
        return;
      }
    }
  }
}

void EventLoop::UpdateChannel(Channel *ch) const { poller_->UpdateChannel(ch); }

void EventLoop::DeleteChannel(Channel *ch) const { poller_->DeleteChannel(ch); }
