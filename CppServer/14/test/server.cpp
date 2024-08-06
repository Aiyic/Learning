#include "Server.h"
#include <iostream>
#include "Buffer.h"
#include "Connection.h"
#include "EventLoop.h"
#include "Socket.h"
#include "util.h"

int main() {
  EventLoop *loop = new EventLoop();
  Server *server = new Server(loop);
  server->OnConnect([](Connection *conn) {
    conn->Read();
    if (conn->GetState() == Connection::State::Closed) {
      conn->Close();
      return;
    }
    {
      std::lock_guard<std::mutex> locker(cout_lock);
      std::cout << "Message from client " << conn->GetSocket()->GetFd() << ": " << conn->ReadBuffer() << std::endl;
    }
    conn->SetSendBuffer(conn->ReadBuffer());
    conn->Write();
  });

  loop->Loop();
  delete server;
  delete loop;
  return 0;
}
