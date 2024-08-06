// search() 用于查找第一个匹配的子序列, 与 find_end() 对应
// search_n() 用于查找连续的 n 个满足条件的元素的子序列

#include <iostream>
#include <algorithm>

using namespace std;

class mycomp2 {
public:
    bool operator()(const int& i, const int& x) {
        return (i%x == 0);
    }
};

int main() {

    vector<int> vi = {4,54,12,4,4,43,5,6,7,3,2,5};
    vector<int> vi2 = {4};              

    auto ret1 = search(vi.begin(), vi.end(), vi2.begin(), vi2.end());
    auto ret2 = find_end(vi.begin(), vi.end(), vi2.begin(), vi2.end());
    cout << distance(vi.begin(),ret1) << ' ' << distance(vi.begin(),ret2) << endl;

    int x=4;
    auto ret3 = search_n(vi.begin(), vi.end(), 2, x); // 查找连续的2个x出现位置，也可以使用仿函数自定义规则，如连续2个可以被x整除的数
    cout << distance(vi.begin(),ret3) << endl;

}

