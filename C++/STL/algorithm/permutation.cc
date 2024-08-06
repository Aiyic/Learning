// is_permutation 检查一个序列是不是另一个序列的排列
// next_permutation 生成下一个更大的排列，直接原地修改序列，返回bool，当前为最大序列时返回false
// prev_permutation 生成下一个更大的排列

#include <iostream>
#include <algorithm>

using namespace std;

int main() {

    vector<int> vi = {1,2,3,4,5};
    vector<int> vi2 = {1,5,3,4,2};

    bool t = is_permutation(vi.begin(),vi.end(), vi2.begin(),vi2.end());

    std::vector<int> range {1,2,3,4};
    do {
        for(auto & x : range)
            cout << x << ' ';
        cout << endl;
    }while(std::next_permutation(std::begin(range), std::end(range)));
    // 返回false, 但此时序列已变为最小

    cout << "prev" << endl;
    std::prev_permutation(std::begin(range), std::end(range));
    // 返回false, 将序列变为最大
    do {
        for(auto & x : range)
            cout << x << ' ';
        cout << endl;
    }while(std::prev_permutation(std::begin(range), std::end(range)));
}

