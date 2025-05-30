#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int rob(vector<int>& nums) {
        int n=nums.size();
        if(n==1) return nums[0];
        vector<array<int,2>> dp(n+1);
        dp[0][1]=nums[0];
        dp[1][1]=nums[1];
        dp[0][0]=0;
        dp[1][0]=dp[0][1];
        for(int i=2; i<n; ++i){
            dp[i][1] = max(dp[i-1][0], dp[i-2][1]) + nums[i];
            dp[i][0] = max(dp[i-1][1], dp[i-2][1]);
        }
        return max(dp[n-1][0], dp[n-1][1]);
    }
};


int main() {
    Solution s;
    vector<int> nums={2,1};
    auto a = s.rob(nums);
    cout << a;
    return 0;
}
