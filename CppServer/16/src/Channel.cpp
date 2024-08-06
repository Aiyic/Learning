/**
 * @file Channel.cpp
 * @author 冯岳松 (yuesong-feng@foxmail.com)
 * @brief
 * @version 0.1
 * @date 2022-01-04
 *
 * @copyright Copyright (冯岳松) 2022
 *
 */
#include "Channel.h"

#include <unistd.h>

#include <utility>
#include <iostream>

#include "EventLoop.h"
#include "Socket.h"

const int8_t Channel::READ_EVENT = 1;
const int8_t Channel::WRITE_EVENT = 2;
const int8_t Channel::ET = 4;

Channel::Channel(int fd, EventLoop *loop) : fd_(fd), loop_(loop), listen_events_(0), ready_events_(0), exist_(false) {}

Channel::~Channel() { 
  loop_->DeleteChannel(this);  
}

void Channel::HandleEvent() const {
  if (ready_events_ & READ_EVENT) {
    read_callback_();
  }
  if (ready_events_ & WRITE_EVENT) {
    write_callback_();
  }
}

void Channel::EnableRead() {
  listen_events_ |= READ_EVENT;
  loop_->UpdateChannel(this);
}

void Channel::EnableWrite() {
  listen_events_ |= WRITE_EVENT;
  loop_->UpdateChannel(this);
}

void Channel::EnableET() {
  listen_events_ |= ET;
  loop_->UpdateChannel(this);
}
int Channel::GetFd() const { return fd_; }

uint32_t Channel::ListenEvents() const { return listen_events_; }
uint32_t Channel::ReadyEvents() const { return ready_events_; }

bool Channel::Exist() const { return exist_; }

void Channel::SetExist(bool in) { exist_ = in; }

void Channel::SetReadyEvent(uint32_t ev) {
  if (ev & READ_EVENT) {
    ready_events_ |= READ_EVENT;
  }
  if (ev & WRITE_EVENT) {
    ready_events_ |= WRITE_EVENT;
  }
  if (ev & ET) {
    ready_events_ |= ET;
  }
}

void Channel::SetReadCallback(std::function<void()> const &callback) { read_callback_ = callback; }
void Channel::SetWriteCallback(std::function<void()> const &callback) { write_callback_ = callback; }
