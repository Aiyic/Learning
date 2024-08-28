/*
   用于在(编译的时候)推导出一个[(可调用对象)(可调用对象)(可调用对象)](函数,std::funciton或者重载了operator()操作的对象等)的返回值类型.主要用于模板编写中.
*/

#include <iostream>
#include <type_traits>

int fun(int) { return 1; }

class Base{
public:
    int operator()(int){return 1;}
};

int main() {
    using A = typename std::result_of<decltype(fun)&(int)>::type;
    using A = typename std::result_of<Base(int)>::type;
    using x = decltype(fun);
    return 0;
}