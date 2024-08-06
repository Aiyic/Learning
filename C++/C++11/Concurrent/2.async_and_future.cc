
// std::future 析构函数会阻塞，直到线程结束。
// 通常我们认为 std::future::get() 和 std::future::wait() 才会阻塞，析构函数同样也会。

#include <thread>
#include <future>
#include <iostream>

auto sleep = [](int s) { std::this_thread::sleep_for(std::chrono::seconds(s)); };

int main(){
    std::async( std::launch::async, sleep, 5 ); // 临时对象被析构，阻塞 5s
    std::cout << "async 1" << std::endl;
    std::async( std::launch::async, sleep, 5 ); // 临时对象被析构，阻塞 5s
    std::cout << "async 2" << std::endl;
    
    auto f1 = std::async( std::launch::async, sleep, 5 );    
    std::cout << "async 3 and ";
    auto f2 = std::async( std::launch::async, sleep, 5 );
    std::cout << "async 4" << std::endl;

    // 返回的future对象析构会等待异步任务执行完毕
}

