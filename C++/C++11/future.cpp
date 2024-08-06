#include<iostream>
#include<vector>
#include<queue>
#include<functional>
#include<future>


#if 0
//线程池中的期约
class ThreadPool {
public:
    ThreadPool(size_t);
    // class... A template parameter pack is a template parameter that accepts zero or more template arguments
    // https://en.cppreference.com/w/cpp/language/parameter_pack
    template<class F, class... Args>
    // auto enqueue(F&& f, Args&&... args)->std::future<typename std::result_of<F(Args...)>::type>;
    std::future<typename std::result_of<F(Args...)>::type> enqueue(F&& f, Args&&... args);
    ~ThreadPool();
private:
    // need to keep track of threads so we can join them
    std::vector<std::thread> workers;
    // the task queue
    std::queue<std::function<void()>> tasks;

    // synchronization
    std::mutex queue_mutex;
    std::condition_variable condition;
    bool stop;
};
// add new work item to the pool
template<class F, class... Args>
std::future<typename std::result_of<F(Args...)>::type> ThreadPool::enqueue(F&& f, Args&&... args) {
    // 当可调用对象F传入参数Args...时的返回值类型
    using return_type = typename std::result_of<F(Args...)>::type;
    // https://en.cppreference.com/w/cpp/thread/packaged_task
    // The class template std::packaged_tash wraps any Callable target so that it can be invoked asynchronously.
    // Its return value or exception thrown is stored in a shared state which can be accessed through std::future objects.
    // 完美转发：https://tjsw.medium.com/%E6%BD%AE-c-11-perfect-forwarding-%E5%AE%8C%E7%BE%8E%E8%BD%89%E7%99%BC%E4%BD%A0%E7%9A%84%E9%9C%80%E6%B1%82-%E6%B7%B1%E5%BA%A6%E8%A7%A3%E6%9E%90-f991830bcd84

    // 当构造一个packaged_task实例的时候，必须传入一个函数或可调用对象
    // std::bind(F&& f, Args&&... args)返回的可调用对象，所需的参数为空，函数形式为std::result_of<F(Args...)>::type()
    // 因此如果构造一个bind的任务，就相当于是下面这种形式
    // std::packaged_task<return_type()>(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
    auto task = std::make_shared<std::packaged_task<return_type()>>(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
    // get_future returns a std::future associated with the promised result
    std::future<return_type> res = task->get_future();
    {
        std::lock_guard<std::mutex> lock(queue_mutex);
        // don't allow enqueueing after stopping the pool
        if(stop) {
            throw std::runtime_error("enqueue on stopped ThreadPool");
        }
        // packaged_task类有operator()，执行函数
        tasks.emplace([task]() { (*task)(); });
    }
    condition.notify_one();
    return res;
}
#endif



int fun(int x){return x;}
int main()
{
    // 如何给它传入固定参数, 而不必在调用时指定
    // std::packaged_task<int(int)> t(fun);
    std::packaged_task<int()> t(std::bind(fun, 6));

    // do something else

    t(); // in a different context， always return void
    int x = t.get_future().get();
    std::cout << x << std::endl;
    return 0;
}