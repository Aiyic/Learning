/*

int等内部类型没有移动构造函数。
移动语义的意思是说 当右侧是右值的时候，编译器会先去查找当前的类型是否有移动构造函数，没有会去调用拷贝构造。
也就是说移动构造只是一个普通的函数，但我们应该在移动构造里面做的是 将右值资源转移到左值。这就是移动语义。
move指的是强制转换为右值，来达到显式调用移动构造的目的。

*/

#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> v;
    // push_back(int &&__x)
    v.push_back(2); 
    return 0;
}