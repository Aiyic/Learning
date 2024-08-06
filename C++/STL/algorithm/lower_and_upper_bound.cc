// 二分法查找函数,仅限有序,返回迭代器

#include <iostream>
#include <algorithm>

using namespace std;

int main() {

    vector<int> vi = {4,54,12,4,2,43,5,6,7,3,2,5};
    sort(vi.begin(),vi.end());
    
    // 查找不小于(>=)目标值的第一个元素
    auto it = lower_bound(vi.begin(),vi.end(), 5);
    // 查找大于(>)目标值的第一个元素
    auto it2 = upper_bound(vi.begin(),vi.end(), 5);

    for(auto & x : vi)
        cout << x << ' ';
    cout << endl;
}

