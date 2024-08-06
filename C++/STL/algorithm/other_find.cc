
// find_end() 用于查找最后一个匹配的子序列
// find_first_of() 在 A 序列中查找和 B 序列中任意元素相匹配的第一个元素

#include <iostream>
#include <algorithm>

using namespace std;

int main() {

    vector<int> vi = {4,54,12,4,2,43,5,6,7,3,2,5};
    vector<int> vi2 = {4};              

    auto ret2 = find_end(vi.begin(), vi.end(), vi2.begin(), vi2.end());

    for(auto & x : vi)
        cout << x << ' ';
    cout << endl;

    string url = "http://123123123";
    string ch = "st";
    // url 第二个t匹配
    auto it = find_first_of(url.begin(), url.end(), ch.begin(), ch.end());

    cout << *it << endl;
}

