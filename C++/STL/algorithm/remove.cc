
// remove并不真的删除元素，返回新的end()位置，可以配合eraer()删除尾部多余元素

#include <iostream>
#include <algorithm>

using namespace std;

int main() {

    vector<int> vi = {4,54,12,4,2,43,5,6,7,3,2,5};

    auto it = remove(vi.begin(),vi.end(), 4);

    for(auto & x : vi)
        cout << x << ' ';
    cout << endl;
}

