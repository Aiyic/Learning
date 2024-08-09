#include <unistd.h>
#include <iostream>
#include "pine.h"

void OneClient(int msgs, int wait) {
  Socket *sock = new Socket();
  RC ret = sock->Create();
  if (ret == RC_SOCKET_ERROR) {
    std::lock_guard<std::mutex> locker(cout_lock);
    std::cerr << "RC_SOCKET_ERROR" << std::endl;
  }
  ret = sock->Connect("127.0.0.1", 1234);
  if (ret == RC_SOCKET_ERROR) {
    std::lock_guard<std::mutex> locker(cout_lock);
    std::cerr << "RC_SOCKET_ERROR" << std::endl;
  }

  Connection *conn = new Connection(sock->GetFd(), nullptr);
  sleep(wait);

  int count = 0;
  while (count < msgs) {
    conn->SetSendBuf("I'm client!");
    conn->Write();
    if (conn->GetState() == Connection::State::Closed) {
      conn->Close();
      break;
    }
    conn->Read();
    std::lock_guard<std::mutex> locker(cout_lock);
    std::cout << "msg count " << count++ << ": " << conn->ReadBuf()->CStr() << std::endl;
  }
  delete sock;
  delete conn;
}

int main() {
  int threads = 100;
  int msgs = 100;
  int wait = 0;
  // int o = -1;
  // const char *optstring = "t:m:w:";
  // while ((o = getopt(argc, argv, optstring)) != -1) {
  //   switch (o) {
  //     case 't':
  //       threads = std::stoi(optarg);
  //     case 'm':
  //       msgs = std::stoi(optarg);
  //     case 'w':
  //       wait = std::stoi(optarg);
  //     case '?':
  //       printf("error optopt: %c\n", optopt);
  //       printf("error opterr: %d\n", opterr);
  //     default: {}
  //   }
  //   break;
  // }

  ThreadPool *poll = new ThreadPool(threads);
  std::function<void()> func = std::bind(OneClient, msgs, wait);
  for (int i = 0; i < threads; ++i) {
    poll->Add(func);
  }

  delete poll;
  return 0;
}
