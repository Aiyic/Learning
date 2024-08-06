


#include <bits/stdc++.h>
#include <boost/functional/factory.hpp>
#include <condition_variable>

class ThreadPool {
public:
  explicit ThreadPool(size_t num_threads) {
    // 使用boost::factory创建线程对象工厂
    auto create_thread = boost::factory<std::unique_ptr<std::thread>>();

    // 创建并启动线程
    for (size_t i = 0; i < num_threads; ++i) {
      threads_.emplace_back(create_thread([this]() { this->threadFunc(); }));
    }
  }

  ~ThreadPool() {
    // 通知线程停止
    {
      std::unique_lock<std::mutex> lock(mutex_);
      stop_flag_ = true;
    }
    condition_.notify_all();

    // 等待线程退出
    for (auto &thread : threads_) {
      thread->join();
    }
  }

  template <typename Func, typename... Args>
  auto submit(Func &&func, Args &&...args)
      -> std::future<typename std::result_of<Func(Args...)>::type> {
    using return_type = typename std::result_of<Func(Args...)>::type;

    // // 创建打包好的任务
    // auto task = std::make_shared<std::packaged_task<return_type()>>(
    //     std::bind(std::forward<Func>(func), std::forward<Args>(args)...));
    auto task = std::make_shared<std::packaged_task<return_type()>>(
        [func, args...]() mutable { return func(args...); });
    // 将任务添加到队列
    {
      std::unique_lock<std::mutex> lock(mutex_);
      tasks_.emplace([task]() { (*task)(); });
    }

    // 唤醒一个线程处理任务
    condition_.notify_one();

    // 返回任务的future
    return task->get_future();
  }

private:
  void threadFunc() {
    while (true) {
      std::function<void()> task;
      {
        std::unique_lock<std::mutex> lock(mutex_);
        condition_.wait(lock, [this] { return stop_flag_ || !tasks_.empty(); });
        if (stop_flag_ && tasks_.empty()) {
          return;
        }
        task = std::move(tasks_.front());
        tasks_.pop();
      }
      task();
    }
  }

  std::vector<std::unique_ptr<std::thread>> threads_;
  std::queue<std::function<void()>> tasks_;
  std::mutex mutex_;
  std::condition_variable condition_;
  std::atomic<bool> stop_flag_{false};
};

int main() {
  ThreadPool pool(4);

  // 提交任务
  auto future = pool.submit([]() {
    for(int i=0; i<100000; ++i ){
      i=i;
    }
    return 0;
  });

  std::cout << future.get() << std::endl;

  return 0;
}