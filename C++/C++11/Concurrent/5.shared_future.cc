// 与std::future唯一的区别就是多个std::shared_future实例可以引用同一个异步结果。
// std::shared_future可以多次获取结果


#include <iostream>
#include <future>

int main() {
    std::promise<int> ps;
    std::future<int> ft = ps.get_future();
    // std::future右值构造
    std::shared_future<int> sf(std::move(ft)); 


    std::promise<int> ps2;
    // std::future::share()生成
    auto sf2 = ps2.get_future().share();

}