// adjacent_difference 相邻运算：默认为减法, 当前元素和上一个元素做运算操作, 首个元素不做处理

#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

struct my_op
{
    int operator()(int x,int y){
        return x+y;
    }
};

int main() {

    std::vector<int> myvector{ 5,20,5,30,30,20,10,10,20 };
    std::vector<int> res(myvector.size());

    adjacent_difference(myvector.begin(), myvector.end(), res.begin());

    for(auto & x : res)
        cout << x << ' ';
    cout << endl;
    
    adjacent_difference(myvector.begin(), myvector.end(), res.begin(), my_op());

    for(auto & x : res)
        cout << x << ' ';
    cout << endl;
}

