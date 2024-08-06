// 折叠表达式是C++17新引进的语法特性。使用折叠表达式可以简化对C++11中引入的参数包的处理，从而在某些情况下避免使用递归。

#include <iostream>
using namespace std;

template<typename First, typename... Rest>
First sum2(First&& first, Rest&&... rest)
{
    return (first + ... + rest);
}
 
int main()
{
    cout << sum2(1)  << endl;
    cout << sum2(1,2,3,4)  << endl; 
}