// jthread 是c++20对thread的进一步封装
// thread需要在主线程显式调用join等待子线程结束，或detach分离子线程，否则子线程析构时会异常终止
// jthread子线程析构时会自动调用join，等待子线程结束
// jthread​​还支持外部请求中止操作

#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

int main() {
  std::vector<std::jthread> pool;

  for (int i = 0; i < 4; ++i) {
    pool.emplace_back([]() {
      std::this_thread::sleep_for(std::chrono::seconds(1));
      std::cout << "Thread id = " << std::this_thread::get_id() << std::endl;
    });
  }

//   for (auto& t : pool) {
//     t.join();
//   }

  return 0;
}
