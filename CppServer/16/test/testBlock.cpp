#include <Connection.h>
#include <Socket.h>
#include <iostream>
#include <unistd.h>
#include <thread>
#include "pine.h"

int main() {
  Socket sock;
  RC ret = sock.Create();
  if (ret == RC_SOCKET_ERROR) {
    std::cerr << "RC_SOCKET_ERROR" << std::endl;
  }
  ret = sock.Connect("127.0.0.1", 1234);
  if (ret == RC_SOCKET_ERROR) {
    std::cerr << "RC_SOCKET_ERROR" << std::endl;
  }
  
  Connection conn(sock.GetFd(),nullptr);
  
  std::cout << sock.IsNonBlocking() << std::endl;

  return 0;
}
