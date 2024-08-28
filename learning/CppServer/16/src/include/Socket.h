/**
 * @file Socket.h
 * @author 冯岳松 (yuesong-feng@foxmail.com)
 * @brief
 * @version 0.1
 * @date 2022-01-04
 *
 * @copyright Copyright (冯岳松) 2022
 *
 */

#pragma once
#include <string>
#include "common.h"

class Socket {
 public:
  DISALLOW_COPY_AND_MOVE(Socket);
  Socket();
  ~Socket();
  void SetFd(int fd);
  [[nodiscard]] int GetFd() const;
  [[nodiscard]] std::string GetAddr() const;
  [[nodiscard]] RC Create();
  [[nodiscard]] RC Bind(const char *ip, uint16_t port) const;
  [[nodiscard]] RC Listen() const;
  [[nodiscard]] RC Accept(int *clnt_fd) const;
  [[nodiscard]] RC Connect(const char *ip, uint16_t port) const;
  [[nodiscard]] RC SetNonBlocking() const;
  [[nodiscard]] bool IsNonBlocking() const;
  [[nodiscard]] size_t RecvBufSize() const;

 private:
  int fd_ = -1;
};
