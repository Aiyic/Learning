// 合并两个有序序列

#include <iostream>
#include <algorithm>

using namespace std;

int main() {

    vector<int> vi = {1,3,4,5,5};
    vector<int> vi2 = {2,2,3,4};
    vector<int> res;
    res.resize(vi.size()+vi2.size());
    merge(vi.begin(),vi.end(), vi2.begin(),vi2.end(),res.begin());

    for(auto & x : res)
        cout << x << ' ';
    cout << endl;


    vector<int> vi3 = {1,3,4,5,5,2,2,3,4};
    inplace_merge(vi3.begin(), vi3.begin()+5, vi3.end());

    for(auto & x : res)
        cout << x << ' ';
    cout << endl;
}

