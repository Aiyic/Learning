// 智能指针(shared_ptr)线程安全吗?
//     是: 引用计数控制单元线程安全, 保证对象只被释放一次
//     否: 对于数据的读写没有线程安全
// 
// C++20: atomic<shared_ptr<T>>, atomic<weak_ptr<T>>
// 全局非成员原子操作函数标记为不推荐使用(deprecated)
// (gcc v12+支持，v11.4不支持)

#include <iostream>
#include <memory>
#include <atomic>
#include <thread>

struct MyData {
    int value;
};

int main() {
    std::shared_ptr<MyData> data = std::make_shared<MyData>();
    std::atomic<std::shared_ptr<MyData>> atomicPtr(data);
    
    std::thread t1([&]() {
        std::shared_ptr<MyData> localPtr = std::atomic_load(&atomicPtr);
        localPtr->value = 10;
        std::atomic_store(&atomicPtr, localPtr);
    });

    std::thread t2([&]() {
        std::shared_ptr<MyData> localPtr = std::atomic_load(&atomicPtr);
        std::cout << "Value from t2: " << localPtr->value << std::endl;
    });

    t1.join();
    t2.join();

    return 0;
}
