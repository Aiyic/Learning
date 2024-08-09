/**
 * @file TcpServer.h
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
#include <unordered_map>
#include <vector>
#include "common.h"

class TcpServer {
 public:
  DISALLOW_COPY_AND_MOVE(TcpServer);
  TcpServer();
  ~TcpServer();
  void Start();
  void Exit();

  RC NewConnection(int fd);
  RC DeleteConnection(int fd);

  void OnConnect(std::function<void(Connection *)> fn);
  void OnRecv(std::function<void(Connection *)> fn);

  const std::unordered_map<int, std::unique_ptr<Connection>>& GetClients() const;
  
 private:
  
  std::unique_ptr<EventLoop> main_reactor_;
  std::unique_ptr<Acceptor> acceptor_;

  std::vector<std::unique_ptr<EventLoop>> sub_reactors_;
  std::unordered_map<int, std::unique_ptr<Connection>> connections_;

  std::unique_ptr<ThreadPool> thread_pool_;

  std::function<void(Connection *)> on_connect_;
  std::function<void(Connection *)> on_recv_;

};
