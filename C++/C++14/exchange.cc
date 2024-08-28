// exchange(_1,_2) 将_2的值给_1，并返回_1原值
// swap(_1,_2)  将_1,_2的值交换，不返回

#include <vector>
#include <utility>
#include <iostream>

using namespace std;

int main() {
    std::vector<int> v;
    std::exchange(v, {1,2,3,4});
    cout << v.size() << endl;
    for (int a : v) {
        cout << a << " ";
    }
    cout << endl;
    return 0;
}