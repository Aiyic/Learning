// transform 对序列所有元素应用一个可调用对象, 并生成新序列版本, 两个序列类型可以不一样

#include <iostream>
#include <algorithm>

using namespace std;

int main() {

    string chars (30, 'a'); // 30 space characters
    int incr = 0;
    vector<int> out(30);

    transform(
        chars.begin(),
        chars.end(),
        out.begin(),
        [&incr](char c){ incr += 1; return c + (incr % 26);});


    cout << chars << endl;
    for(auto & x : out)
        cout << x << ' ';
    cout << endl;

}


