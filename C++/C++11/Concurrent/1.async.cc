// 使用 std::async 启动一个异步任务，std::async 返回一个 std::future 对象，std::future 对象中存放着最终计算的结果。

#include <future>
#include <iostream>

int do_sth(int x){
    std::cout << "do_sth~\n" << std::endl;
    return x;
};

int main()
{
    //不一定创建新线程，系统自行判断
    std::future<int> the_answer=std::async(do_sth, 5);
    // get阻塞等待结果
    std::cout << "The answer is " << the_answer.get() << std::endl;


    // std::launch::async强制指定新线程运行
    the_answer = std::async(std::launch::async, do_sth, 5);
    // get阻塞等待结果
    std::cout << "The answer is " << the_answer.get() << std::endl;


}
