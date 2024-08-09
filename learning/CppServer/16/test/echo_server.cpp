#include <iostream>
#include "pine.h"

int main() {
  TcpServer *server = new TcpServer();

  Signal::SetSignal(SIGINT, [&] {
    std::cout << "\nServer exit!" << std::endl;
    delete server;
    exit(0);
  });

  server->OnConnect(
    [](Connection *conn) { 
      std::lock_guard<std::mutex> locker(cout_lock);
      std::cout << "New connection fd: " << conn->GetSocket()->GetFd() << std::endl; 
    });

  server->OnRecv([](Connection *conn) {
    {
      std::lock_guard<std::mutex> locker(cout_lock);
      std::cout << "Message from client " << conn->ReadBuf()->CStr() << std::endl;
    }
    conn->Send(conn->ReadBuf()->CStr());
  });

  server->Start();

  return 0;
}
