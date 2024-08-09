#include <iostream>
#include <map>
#include "Connection.h"
#include "EventLoop.h"
#include "Server.h"
#include "Socket.h"

int main() {
  EventLoop *loop = new EventLoop();
  Server *server = new Server(loop);

  const auto& clients = server->GetClients();

  server->NewConnect([&](Connection *conn) {
    int clnt_fd = conn->GetSocket()->GetFd();
    std::cout << "New connection fd: " << clnt_fd << std::endl;
    for (auto &each : clients) {
      Connection *client = each.second;
      client->Send("New connection fd: " + std::to_string(clnt_fd));
    }
  });

  server->OnMessage([&](Connection *conn) {
    int clnt_fd = conn->GetSocket()->GetFd();
    std::cout << "Message from " << clnt_fd << ": " << conn->ReadBuffer() << std::endl;
    for (auto &each : clients) {
      Connection *client = each.second;
      client->Send(std::to_string(clnt_fd) + ": " + conn->ReadBuffer());
    }
  });

  loop->Loop();
  return 0;
}
