// C++17增加std::variant实现类似union的功能，比union更高级
// 例如union里面不能有string这种类型，但std::variant却可以，还可以支持更多复杂类型，如map等

#include <variant>
#include <cstring>
#include <iostream>

using namespace std;

int main() { 
    std::variant<int, std::string> var("hello");
    cout << var.index() << endl;
    var = 123;
    cout << var.index() << endl;

    try {
        var = "world";
        std::string str = std::get<std::string>(var); // 通过类型获取值
        var = 3;
        int i = std::get<0>(var); // 通过index获取对应值
        cout << str << endl;
        cout << i << endl;
    } catch(...) {
        // xxx;
    }
    return 0;
}