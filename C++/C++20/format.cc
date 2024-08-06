// 不展开, 类似Python 的格式化,
// <format> (gcc v13+支持，v11.4不支持)

#include <iostream>
#include <format>

using namespace std;

int main()
{
    string s = std::format("Hello CppCon {}!", 2019);
    
    cout<< s << endl;;
    
    return 0;
}