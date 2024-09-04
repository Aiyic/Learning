#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
int turn = 0; // 当前轮到的线程

void printNumber(int thread_id) {
    for (int i = 0; i <= 100; i+=3) {
        std::unique_lock<std::mutex> lock(mtx);
        // 等待直到轮到当前线程
        cv.wait(lock, [thread_id]() { return turn == thread_id; });

        // 打印数字
        std::cout << i + thread_id<< " ";

        // 切换到下一个线程
        turn = (turn + 1) % 3;
        cv.notify_all(); // 通知其他线程
    }
}

int main() {
    std::thread t1(printNumber, 0); // 线程1
    std::thread t2(printNumber, 1); // 线程2
    std::thread t3(printNumber, 2); // 线程3

    // 等待线程结束
    t1.join();
    t2.join();
    t3.join();

    std::cout << std::endl; // 输出换行
    return 0;
}