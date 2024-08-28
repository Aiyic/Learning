          
// adjacent_find() 相邻查找：用于查找 2 个连续相等的元素

#include <iostream>
#include <algorithm>

using namespace std;

int main() {

    std::vector<int> myvector{ 5,20,5,30,30,20,10,10,20 };
    //调用第一种语法格式
    auto it = adjacent_find(myvector.begin(), myvector.end());

    if (it != myvector.end()) 
        cout << *it << endl;
    
}

