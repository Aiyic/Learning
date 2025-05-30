#include<iostream>
#include<vector>
#include<stack>
#include<functional>
#include<algorithm>

using namespace std;

class Solution {
public:
    // int jump(vector<int>& nums) {
    //     int n=nums.size();
    //     vector<int> dp(n, INT_MAX);
    //     dp[0]=0;
    //     jump2(nums, dp, 0, 0);
    //     return dp[n-1];
    // }

    // int jump2(vector<int>& nums, vector<int>& dp, int idx, int step){
    //     if(step>dp[idx]) return 0;
    //     for(int i=idx+1; i<=idx+nums[idx] && i<nums.size(); i++){
    //         if(step<dp[i]) {
    //             dp[i]=step+1;
    //         }
    //     }
    //     for(int i=idx+nums[idx]; i>idx; i--){
    //         if(i>=nums.size()) continue;
    //         jump2(nums,dp,i,step+1);
    //     }
    //     return 0;
    // }

    int jump(vector<int>& nums) {
        int idx=0,lastidx=0,step=0,temp=0;
        while(idx<nums.size()-1){
            step++;
            temp=idx;
            for(int i=lastidx;i<=idx;i++){
                if(nums[i]+i>temp) temp=nums[i]+i;
            }
            lastidx=idx;
            idx=temp;
        }
        return step;
    }
};

int main() {
    Solution x;
    vector<int> nums={4,6,6,6,3,4,3,5,2,4,5,4,4,4};
    int a = x.jump(nums) ;
    cout << a;
    return 0;
}
