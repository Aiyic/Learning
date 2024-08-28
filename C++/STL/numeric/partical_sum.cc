// partial_sum 局部求和，类似前缀和, 可自定义为累乘等累积运算

#include <iostream>
#include <numeric>
#include <vector>
#include <algorithm>

using namespace std;

struct my_op // 累乘
{
    int operator()(int x,int y){
        return x*y;
    }
};

int main() {

    std::vector<int> myvector{ 1,2,3,4,5 };
    std::vector<int> res(myvector.size());

    partial_sum(myvector.begin(), myvector.end(), res.begin());

    for_each(res.begin(), res.end(), [](int &x){cout << x << ' ';});
    cout << endl;
    
    partial_sum(myvector.begin(), myvector.end(), res.begin(), my_op());

    for_each(res.begin(), res.end(), [](int &x){cout << x << ' ';});
    cout << endl;
}

