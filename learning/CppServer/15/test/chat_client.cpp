#include <Connection.h>
#include <Socket.h>
#include <iostream>
#include <unistd.h>
#include <thread>

int main() {
  Socket *sock = new Socket();
  sock->Connect("127.0.0.1", 1234);
  Connection *conn = new Connection(nullptr, sock);
  
  std::thread th([&](){
    while(true) {
      conn->Read();
      std::cout << conn->ReadBuffer() << std::endl;
    }});
  while (true) {
    std::string str;
    std::cin >> str;
    conn->Send(str);
  }

  delete conn;
  return 0;
}
