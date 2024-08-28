// max_element() 查找序列最大/最小值

#include <iostream>
#include <algorithm>

using namespace std;

int main() {

    vector<int> vi = {4,54,12,4,2,43,5,6,7,3,2,5};

    auto x = max_element(vi.begin(),vi.end());
    auto y = min_element(vi.begin(),vi.end());

    cout << *x << ' ' << *y << endl;
}

