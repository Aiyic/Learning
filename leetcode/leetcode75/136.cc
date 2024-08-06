#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int res=0;
        for(auto & x : nums){
            res ^= x;
        }
        return res;
    }
};

int main() {
    Solution s;
    vector<int> nums={4,1,2,1,2};
    auto a = s.singleNumber(nums);
    cout << a;
    return 0;
}
