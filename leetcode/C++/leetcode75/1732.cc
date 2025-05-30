#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int largestAltitude(vector<int>& gain) {
        int g=0,maxg=0;
        for(int &x : gain){
            g+=x;
            maxg=max(maxg,g);
        }
        return maxg;
    }
};

int main() {
    Solution s;
    vector<int> nums={-5,1,5,0,-7};
    int a = s.largestAltitude(nums) ;
    cout << 1;
    return 0;
}
