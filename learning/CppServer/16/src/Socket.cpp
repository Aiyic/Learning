/**
 * @file Socket.cpp
 * @author 冯岳松 (yuesong-feng@foxmail.com)
 * @brief 客户端、服务器共用 accept，connect都支持非阻塞式IO，但只是简单处理，如果情况太复杂可能会有意料之外的bug
 * @version 0.1
 * @date 2022-01-04
 *
 * @copyright Copyright (冯岳松) 2022
 *
 */
#include "Socket.h"
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cassert>
#include <cstring>
#include <mutex>
#include <iostream>

Socket::Socket() = default;

Socket::~Socket() {
  if (fd_ != -1) {
    close(fd_);
    fd_ = -1;
  }
}

void Socket::SetFd(int fd) { fd_ = fd; }

int Socket::GetFd() const { return fd_; }

std::string Socket::GetAddr() const {
  struct sockaddr_in addr = {};
  socklen_t len = sizeof(addr);
  if (getpeername(fd_, (struct sockaddr *)&addr, &len) == -1) {
    return "";
  }
  std::string ret(inet_ntoa(addr.sin_addr));
  ret += ":";
  ret += std::to_string(htons(addr.sin_port));
  return ret;
}

RC Socket::SetNonBlocking() const {
  if (fcntl(fd_, F_SETFL, fcntl(fd_, F_GETFL) | O_NONBLOCK) == -1) {   
    {
      std::lock_guard<std::mutex> locker(cout_lock);
      std::cerr << "Socket set non-blocking failed" << std::endl;
    }
    return RC_SOCKET_ERROR;
  }
  return RC_SUCCESS;
}

bool Socket::IsNonBlocking() const { return (fcntl(fd_, F_GETFL) & O_NONBLOCK) != 0; }

size_t Socket::RecvBufSize() const {
  size_t size = -1;
  if (ioctl(fd_, FIONREAD, &size) == -1) {
    std::lock_guard<std::mutex> locker(cout_lock);
    std::cerr << "Socket get recv buf size failed" << std::endl;
  }
  return size;
}

RC Socket::Create() {
  assert(fd_ == -1);
  fd_ = socket(AF_INET, SOCK_STREAM, 0);
  if (fd_ == -1) {
    {
      std::lock_guard<std::mutex> locker(cout_lock);
      std::cerr << "Failed to create socket" << std::endl;
    }
    return RC_SOCKET_ERROR;
  }
  return RC_SUCCESS;
}

RC Socket::Bind(const char *ip, uint16_t port) const {
  assert(fd_ != -1);
  struct sockaddr_in addr = {};
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = inet_addr(ip);
  addr.sin_port = htons(port);
  if (::bind(fd_, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
    {
      std::lock_guard<std::mutex> locker(cout_lock);
      std::cerr << "Failed to bind socket" << std::endl;
    }
    return RC_SOCKET_ERROR;
  }
  return RC_SUCCESS;
}

RC Socket::Listen() const {
  assert(fd_ != -1);
  if (::listen(fd_, SOMAXCONN) == -1) {
    {
      std::lock_guard<std::mutex> locker(cout_lock);
      std::cerr << "Failed to listen socket" << std::endl;
    }
    return RC_SOCKET_ERROR;
  }
  return RC_SUCCESS;
}

RC Socket::Accept(int *clnt_fd) const {
  // non-blocking
  assert(fd_ != -1);
  *clnt_fd = ::accept(fd_, nullptr, nullptr);
  if (*clnt_fd == -1) {
    {
      std::lock_guard<std::mutex> locker(cout_lock);
      std::cerr << "Failed to accept socket" << std::endl;
    }
    return RC_SOCKET_ERROR;
  }
  return RC_SUCCESS;
}

RC Socket::Connect(const char *ip, uint16_t port) const {
  // non-blocking
  struct sockaddr_in addr = {};
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = inet_addr(ip);
  addr.sin_port = htons(port);
  if (::connect(fd_, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
    {
      std::lock_guard<std::mutex> locker(cout_lock);
      std::cerr << "Failed to connect socket" << std::endl;
    }
    return RC_SOCKET_ERROR;
  }
  return RC_SUCCESS;
}
