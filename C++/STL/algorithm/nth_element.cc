// nth_element()基于折半和递归将第n个元素置于正确的位置，时间复杂度O(n)

#include <iostream>
#include <algorithm>

using namespace std;

int main() {

    vector<int> vi = {4,54,12,4,2,43,5,6,7,3,2,5};

    nth_element(vi.begin(),vi.begin()+2,vi.end());

    for(auto & x : vi)
        cout << x << ' ';
    cout << endl;
}

