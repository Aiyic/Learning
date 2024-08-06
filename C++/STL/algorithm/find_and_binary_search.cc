// find() 是一种线性搜索算法,复杂度O(n),适用于任何类型的容器
// binary_search() 仅适用于已排序的序列,返回bool值

#include <iostream>
#include <algorithm>

using namespace std;

int main() {

    vector<int> vi = {4,54,12,4,2,43,5,6,7,3,2,5};

    auto it = binary_search(vi.begin(),vi.end(), 4);
    auto it2 = find(vi.begin(),vi.end(), 4);
    auto ret2 = find_if(vi.begin(), vi.end(),
		                [](int v) {return v == 4; });

    for(auto & x : vi)
        cout << x << ' ';
    cout << endl;
}

