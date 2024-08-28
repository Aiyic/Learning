// tuple C++元组, 可用于代替结构体

#include <iostream>
#include <tuple>
#include <functional>
 
using namespace std;

int main ()
{
    tuple<int, char, double> mytuple (10, 'a', 3.14);

    cout << "mytuple has ";
    cout << tuple_size<decltype(mytuple)>::value;
    cout << " elements." << '\n';

    //获取元素, get返回的是引用, 可以修改
    cout << "the elements is: ";
    cout << std::get<0>(mytuple) << " ";
    cout << std::get<1>(mytuple) << " ";
    cout << std::get<2>(mytuple) << " ";
    cout << '\n';

    return 0;   
}
 
