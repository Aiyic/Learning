#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <thread>

volatile int counter = 0;

void *increment(void *arg) {
    for (int i = 0; i < 1000000; i++) {
        counter++; // 非原子
    }
    return NULL;
}

int main() {
    // pthread_t thread1, thread2;

    // // 创建两个线程，分别执行increment函数
    // pthread_create(&thread1, NULL, increment, NULL);
    // pthread_create(&thread2, NULL, increment, NULL);

    // // 等待两个线程执行完毕
    // pthread_join(thread1, NULL);
    // pthread_join(thread2, NULL);


    auto t1=std::jthread(increment,nullptr);
    auto t2=std::jthread(increment,nullptr);

    t1.join();
    t2.join();
    printf("Counter: %d\n", counter);

    return 0;
}

