// 构造函数模板推导, 构造函数可省略模板参数列表

#include <iostream>
#include <vector>

using namespace std;

int main() {
    // before c++17
    pair<int,double> p(1, 2.2); 
    vector<int> v(5, 6);
    vector<double> vv{1.1, 2.2, 3.0};

    // c++17
    pair p2(1, 2.2); 
    vector v2(5, 6);
    vector vv2{1.1, 2.2, 3.0};

    cout << endl;
    return 0;
}