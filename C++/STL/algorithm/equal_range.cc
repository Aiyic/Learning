// equal_range 二分法查找函数,仅限有序,返回迭代器
// equal 比较序列长度和对应元素的值
// mismatch 返回不匹配的位置

#include <iostream>
#include <algorithm>

using namespace std;

int main() {

    vector<int> vi = {4,54,12,4,2,43,5,6,7,3,2,5};
    sort(vi.begin(),vi.end());
    for(auto & x : vi)
        cout << x << ' ';
    cout << endl;

    auto it = equal_range(vi.begin(),vi.end(), 4);

    cout << distance(vi.begin(),it.first) << ' ' << distance(vi.begin(),it.second) << endl;

    vector<int> vi2 = {2,2,3,4};
    auto cmp = equal(vi2.begin(), vi2.end(), vi.begin());
    cout << cmp << endl;

    vector<int> vi2 = {2,2,3,4,3};
    auto pairs = mismatch(vi2.begin(), vi2.end(), vi.begin());

}

