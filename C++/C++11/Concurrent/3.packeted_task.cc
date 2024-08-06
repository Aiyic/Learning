// std::packaged_task包装任何可调用对象，抽象程度较async更底层
// 它的返回值或抛出的异常被存储于能通过std::future对象访问的共享状态中

#include <thread>
#include <future>
#include <iostream>

int main(){
    auto task = [](int i) { 
        std::this_thread::sleep_for(std::chrono::seconds(5)); 
        return i+100; 
    };

    std::packaged_task< int(int) > package{ task };
    std::future<int> f = package.get_future();

    // 在当前线程执行，相当于std::launch::deferred
    // package(1);

    // 创建新线程执行，相当于std::launch::async
    std::thread t { std::move(package), 5 };

    // 阻塞等待异步任务结果
    std::cout << f.get() << "\n";

    t.join();
}

