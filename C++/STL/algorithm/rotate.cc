// rotate 原地旋转一个序列
// rotate_copy 旋转并生成一个序列

#include <iostream>
#include <algorithm>

using namespace std;

int main() {

    vector<int> vi = {1,2,3,4,5,6,7,8};
    auto a = rotate(vi.begin(), vi.begin()+2, vi.end());

    vector<int> out(vi.size());
    auto b = rotate_copy(vi.begin(), vi.begin()+2, vi.end(),out.begin());

    for(auto &x : vi)
        cout << x << ' ';
    cout << endl;

}


