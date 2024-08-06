// sort等算法省略begin() end()对

#include <vector>
#include <ranges>
#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    vector<int> vec{3,5,2,8,10};
    ranges::sort(vec);  // 省略
    for(auto i:vec)
    {
        cout<< i<<" ";
    }
    return 0;
}