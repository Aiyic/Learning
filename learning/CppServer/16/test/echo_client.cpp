#include <iostream>
#include "pine.h"

int main() {
  Socket *sock = new Socket();
  RC ret = sock->Create();
  if (ret == RC_SOCKET_ERROR) {
    std::cerr << "RC_SOCKET_ERROR" << std::endl;
  }
  ret = sock->Connect("127.0.0.1", 1234);
  if (ret == RC_SOCKET_ERROR) {
    std::cerr << "RC_SOCKET_ERROR" << std::endl;
  }

  Connection *conn = new Connection(sock->GetFd(), nullptr);

  while (true) {
    std::string input;
    std::getline(std::cin, input);
    conn->SetSendBuf(input.c_str());
    conn->Write();
    if (conn->GetState() == Connection::State::Closed) {
      conn->Close();
      break;
    }
    if(conn->Read()!=RC_SUCCESS) break;
    std::cout << "Message from server: " << conn->ReadBuf()->CStr() << std::endl;
  }

  delete conn;
  delete sock;
  return 0;
}
