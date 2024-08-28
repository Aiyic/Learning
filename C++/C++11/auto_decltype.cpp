/*
   总结：
    decltype(exp) exp为表达式，可计算出表达式的类型(不计算表达式)(为exp加上括号会得到exp的引用类型)
    auto 根据右值类型自动初始化左值对象(可能会忽略右值的顶层const修饰)

*/

#include <iostream>
#include <typeinfo>

using namespace std;

int main()
{
    int a = 3;
    auto c1 = a;
    decltype(a) c2 = a;
    decltype((a)) c3 = a;

    const int d = 5;
    auto f1 = d;
    decltype(d) f2 = d;

    cout << typeid(c1).name() << endl;
    cout << typeid(c2).name() << endl;
    cout << typeid(c3).name() << endl;
    cout << typeid(f1).name() << endl;
    cout << typeid(f2).name() << endl;

    c1++;
    c2++;
    c3++;
    f1++;
    // f2++;   //错误，f2是整型常量，不能执行自增操作

    cout << c1 << " " << c2 << " " << c3 << " " 
        <<f1 << " " << f2 << endl;

    return 0;
}