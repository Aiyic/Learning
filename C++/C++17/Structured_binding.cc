// 结构化绑定，对于vector, map, pair, tuple这类多元素对象可以使用 [x,y ... ] 来结构化绑定一个对象

#include <iostream>
#include <vector>

using namespace std;

int main() {
    std::pair a(1, 2.3f);
    auto& [i, f] = a; // 可以使用引用传递
    i = 2;
    cout << a.first << endl; // 2

    vector<pair<int, int>> v={{1,2}, {3,4}};
    for(auto & [x,y] : v){
        x++;y++;
        cout << x << ' ' << y << endl;
    }

    int array[3] = {1, 2, 3};
    auto [a, b, c] = array;
}