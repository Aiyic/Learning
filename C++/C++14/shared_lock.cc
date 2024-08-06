
// std::shared_timed_mutex
// c++14引入的读写锁，可以多个读，但只有一个写
// 通过shared_lock<shared_timed_mutex>创建读锁
// 通过unique_lock<shared_timed_mutex>创建写锁
// 多个读锁可以同时运行，但是如果写锁被加锁了，那么其他写锁或读锁都会被阻塞

#include <iostream>
#include <shared_mutex>
#include <mutex>
#include <future>

struct ThreadSafe {
    mutable std::shared_timed_mutex mutex_;
    int value_;

    ThreadSafe() {
        value_ = 0;
    }

    int get() const {
        std::shared_lock<std::shared_timed_mutex> loc(mutex_);
        return value_;
    }

    void increase() {
        std::unique_lock<std::shared_timed_mutex> lock(mutex_);
        value_ += 1;
    }
};

int main(){
    ThreadSafe ts;

    auto writer = [&](){
        ts.increase();
    };
    auto reader = [&](){
        return ts.get();
    };

    auto write = std::async(std::launch::async, writer);
    auto read = std::async(std::launch::async, reader );


}