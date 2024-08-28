// 让函数返回一个obj对象, 如果异常就返回一个"空"
// 常规方式只能通过返回对象指针，异常就返回nullptr这类实现
// std::optional<obj> 可以指定返回std::nullopt来代指空对象


#include <iostream>
#include <optional>

using namespace std;

std::optional<int> StoI(const std::string &s) {
    try {
        return std::stoi(s);
    } catch(...) {
        return std::nullopt;
    }
}

int main() {
    std::string s{"123"};
    std::optional<int> o = StoI(s);
    if (o) {
        cout << *o << endl;
    } else {
        cout << "error" << endl;
    }    
    
    s="";
    std::optional<int> o2 = StoI(s);
    if (o2) {
        cout << *o2 << endl;
    } else {
        cout << "error" << endl;
    }
}
