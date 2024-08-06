// promise可以将一个值传递给新进程，而不需要任何额外的同步操作。
// 抽象程度最底层

#include <thread>
#include <future>
#include <iostream>

int main(){
    auto task = [](std::future<int> i) {
        std::cout << i.get() << std::flush; // 阻塞，直到 p.set_value() 被调用
    };

    std::promise<int> p;
    std::thread t(task, p.get_future()) ;

    std::this_thread::sleep_for(std::chrono::seconds(5));
    // 通过 std_value() 方法来传递数据
    p.set_value(5);

    t.join();
}


