#include "muduo/base/AsyncLogging.h"
#include "muduo/base/Logging.h"
#include "muduo/base/Timestamp.h"

#include <cstddef>
#include <cstdio>
#include <sys/resource.h>
#include <unistd.h>

#include <cstddef>

off_t k_roll_size = static_cast<off_t>(500*1000*1000);

muduo::AsyncLogging* g_async_log = NULL;

void asyncOutput(const char* msg, int len)
{
  g_async_log->append(msg, len);
}

void bench(bool longLog)
{
  muduo::Logger::setOutput(asyncOutput);

  int cnt = 0;
  const int k_batch = 1000;
  muduo::string empty = " ";
  muduo::string long_str(3000, 'X');
  long_str += " ";

  for (int t = 0; t < 30; ++t)
  {
    muduo::Timestamp start = muduo::Timestamp::now();
    for (int i = 0; i < k_batch; ++i)
    {
      LOG_INFO << "Hello 0123456789" << " abcdefghijklmnopqrstuvwxyz "
               << (longLog ? long_str : empty)
               << cnt;
      ++cnt;
    }
    muduo::Timestamp end = muduo::Timestamp::now();
    printf("%f\n", timeDifference(end, start)*1000000/k_batch);
    struct timespec ts = { 0, k_roll_size };
    nanosleep(&ts, NULL);
  }
}

int main(int argc, char* argv[])
{
  {
    // set max virtual memory to 2GB.
    auto k_one_gb = static_cast<size_t>(1000*1024*1024);
    rlimit rl = { 2*k_one_gb, 2*k_one_gb };
    setrlimit(RLIMIT_AS, &rl);
  }

  printf("pid = %d\n", getpid());

  char name[256] = { '\0' };
  strncpy(name, argv[0], sizeof name - 1);
  muduo::AsyncLogging log(::basename(name), k_roll_size);
  log.start();
  g_async_log = &log;

  bool long_log = argc > 1;
  bench(long_log);
}
