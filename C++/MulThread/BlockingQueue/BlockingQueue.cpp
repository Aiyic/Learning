#include <iostream>
#include <thread>
#include <mutex>
#include <random>
#include <algorithm>
#include <atomic>

#include <unistd.h>

#include "blockingqueue.h"
using namespace std;

int task=30;
BlockingQueue<int> blockingqueue;
std::mutex mutex_cout;
std::mutex mutex_no;
std::vector<thread::id> th_workers_no;
std::atomic<int> task_no(0);

void worker(){
    int value,idx;
    thread::id this_id = this_thread::get_id();
    {
        std::lock_guard<std::mutex> lock_no(mutex_no);
        auto it = find(th_workers_no.begin(), th_workers_no.end(),this_id);
        if(it!=th_workers_no.end()){
            idx=distance(th_workers_no.begin(), it);
        }
        else{
            idx=th_workers_no.size();
            th_workers_no.push_back(this_id); // vector不是线程安全的，有写覆盖的可能，加锁保护
        } // 获取子线程编号
    }
  
    while(true){
        value = blockingqueue.take();
        if(!value){
            std::lock_guard<std::mutex> lock(mutex_cout);
            std::cout << "workder: " << this_id 
                    << " NO: " << idx
                    << " exit" 
                    << std::endl;
            return;
        }
        uint64_t sum = 0;
        for(int i = 0; i < value; i++){
            sum += i;
        }

        usleep(500*1000);
        
        // 为cout加锁防止多线程输出错位
        {
            std::lock_guard<mutex> lock(mutex_cout);
            std::cout << "workder: " << this_id 
                    << " NO: " << idx
                    << " task: " << task_no++
                    << " value: " << value
                    << " sum: " << sum
                    << std::endl;
        }
    }
}

void master(){
    srand(time(nullptr));
    for(int i = 0; i < task; i++){
        int value = rand()%10000;
        blockingqueue.push(value);
        usleep(60*1000);
        {
            std::lock_guard<mutex> lock(mutex_cout);
            std::cout << "master "  
                    << " task: " << i 
                    << " value: " << value 
                    << " sum: " << value*(value-1)/2
                    << std::endl;
        }
    }
    blockingqueue.exit();//线程安全？？？

    /*--------------------更好的实现？？？----------------------*/
    // for(int i=0; i < 5; i++){
    //     blockingqueue.push(0);  //线程安全！！！
    //     // 为每个子线程发送终止信号
    // }
}

int main(){
    thread th_master(master);
    std::vector<thread> th_workers;
    for(int i=0; i < 5; i++){
        th_workers.emplace_back(thread(worker));
    }

    th_master.join();
    // 此时master已经结束返回，即没有新的任务了
    // 但程序不能结束，因为子线程还未返回，直接结束会导致子线程异常终止
    for (std::thread& worker_thread : th_workers) {
        if (worker_thread.joinable()) {
            worker_thread.join();  // 等待每个子线程完成任务
            // 这里如果调用detach，也能正常返回，但阻塞队列可能还有未完成的任务未被执行
        }
    }
    return 0;
}

