// views: 延迟计算(遍历时才计算), 不持有, 不改写
// 使用管道符|串联

#include <vector>
#include <ranges>
#include <iostream>

using namespace std;

int main()
{
    vector<int> data {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; 
    auto result = data | 
                  views::transform([](int i) { return i*i; })  | 
                  views::transform([](int i) { return to_string(i); }); 

    for(auto x : result)
        cout << x << ' ';
    cout << endl;
    return 0;
}

