// replace 对序列所有元素进行查找替换

#include <iostream>
#include <algorithm>
#include <deque>

using namespace std;

int main() {

    std::deque<int> data {10, -5, 12, -6, 10, 8, -7, 10, 11};
    std::replace(std::begin(data), std::end(data), 10, 99);

    for(auto & x : data)
        cout << x << ' ';
    cout << endl;

}


