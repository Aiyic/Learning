#ifndef BLOCKINGQUEUE_H
#define BLOCKINGQUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>
#include <assert.h>

template <typename T>
class BlockingQueue
{
public:
    BlockingQueue():_mutex(), _condition(), _data(), _exit(false){}

    // 禁止拷贝构造
    BlockingQueue(BlockingQueue&) = delete;

    ~BlockingQueue(){}

    void push(T&& value) {
        // 往队列中塞数据前要先加锁
        std::unique_lock<std::mutex> lock(_mutex);
        _data.push(value);
        _condition.notify_all();
    }

    void push(const T& value){
        std::unique_lock<std::mutex> lock(_mutex);
        _data.push(value);
        _condition.notify_all();
    }

    T take() {
        std::unique_lock<std::mutex> lock(_mutex);
        while(_data.empty() ){
            if(_exit) return 0;        // 更好的实现？？？
            _condition.wait(lock);
        }  

        assert(!_data.empty());
        T value(std::move(_data.front()));
        _data.pop();

        return value;
    }

    size_t size() const {
        std::unique_lock<std::mutex> lock(_mutex);
        return _data.size();
    }

    void exit(){    // 线程安全？？？
        std::unique_lock<std::mutex> lock(_mutex);
        _exit=true;
        _condition.notify_all();
    }

private:
    // 实际使用的数据结构队列
    std::queue<T> _data;

    // 条件变量的锁
    std::mutex _mutex;
    std::condition_variable _condition;


    //控制结束 线程安全？？？
    bool _exit;

};
#endif // BLOCKINGQUEUE_H
