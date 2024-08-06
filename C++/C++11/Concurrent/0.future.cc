// std::future只能 get() 一次，多次get会抛出异常

#include <iostream>
#include <future>
#include <thread>

// 一个有效(valid)的 std::future 对象通常由以下三种 Provider 创建，并和某个共享状态相关联。Provider 可以是函数或者类，他们分别是：
//     std::async 函数
//     std::packaged_task::get_future，此时 get_future为 packaged_task 的成员函数
//     std::promise::get_future，get_future 为 promise 类的成员函数
// 由 std::future 默认构造函数创建的 future 对象不是有效的，需要 move 赋值另一个有效的 future 对象