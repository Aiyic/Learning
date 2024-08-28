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
    return 0;
  }
  ret = sock.Connect("127.0.0.1", 1234);
  if (ret == RC_SOCKET_ERROR) {
    std::cerr << "RC_SOCKET_ERROR" << std::endl;
    return 0;
  }
  
  Connection conn(sock.GetFd(),nullptr);
  
  std::thread th([&](){
    while(true) {
      if(conn.Read()!=RC_SUCCESS) return;
      std::cout << conn.ReadBuf()->CStr() << std::endl;
    }});
  while (true) {
    std::string str;
    std::cin >> str;
    if(conn.Send(str)!=RC_SUCCESS) return 0;
  }

  return 0;
}
