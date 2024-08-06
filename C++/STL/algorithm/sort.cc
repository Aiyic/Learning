// sort()基于快排不稳定，stable_sort为稳定版本基于归并排序

#include <iostream>
#include <algorithm>

using namespace std;

int main() {

    vector<int> vi = {4,54,12,4,2,43,5,6,7,3,2,5};

    // sort(vi.begin(),vi.end());
    stable_sort(vi.begin(),vi.end());

    for(auto & x : vi)
        cout << x << ' ';
    cout << endl;
}

