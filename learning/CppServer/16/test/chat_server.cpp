#include <iostream>
#include <map>
#include "Connection.h"
#include "EventLoop.h"
#include "TcpServer.h"
#include "Socket.h"
#include "Buffer.h"

int main() {
  TcpServer *server = new TcpServer();

  const auto& clients = server->GetClients();

  server->OnConnect([&](Connection *conn) {
    int clnt_fd = conn->GetSocket()->GetFd();
    std::cout << "New connection fd: " << clnt_fd << std::endl;
    for (auto &each : clients) {
      each.second->Send("New connection fd: " + std::to_string(clnt_fd));
    }
  });

  server->OnRecv([&](Connection *conn) {
    int clnt_fd = conn->GetSocket()->GetFd();
    std::cout << "Message from " << clnt_fd << ": " << conn->ReadBuf()->CStr() << std::endl;
    for (auto &each : clients) {
      each.second->Send(std::to_string(clnt_fd) + ": " + conn->ReadBuf()->CStr());
    }
  });

  server->Start();
  return 0;
}
