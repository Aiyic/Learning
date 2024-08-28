// unique 序列去重

#include <iostream>
#include <algorithm>

using namespace std;

int main() {

    vector<int> vi = {1,2,3,4,4,4,5};
    auto newend = unique(vi.begin(),vi.end());

    vi.erase(newend,vi.end());

    for(auto &x : vi)
        cout << x << ' ';
    cout << endl;

}


