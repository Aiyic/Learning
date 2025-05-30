#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxSubArray(vector<int>& nums) {

        int ans = INT_MIN, cur = 0;
        for (const auto &i : nums) {
            cur = max(i , cur + i);
            ans = max(ans, cur);
        }
        return ans;

        return maxSubArray2(nums,0,nums.size());
    }
    int maxSubArray2(vector<int>& nums, int left, int right){

        int n=right-left;
        if(n==1) return nums[left];
        int half=n/2;
        int x1=0,x2=0;
        int maxx1=INT_MIN,maxx2=INT_MIN;

        int res=max(maxSubArray2(nums,left,left+half),maxSubArray2(nums,left+half,right));

        for(int i=left+half-1;i>=left;i--) {
            x1+=nums[i];
            if(x1>maxx1)  maxx1=x1;
        }
        for(int i=left+half;i<right;i++) {
            x2+=nums[i];
            if(x2>maxx2)  maxx2=x2;
        }
        return max(res,maxx1+maxx2);
    }

};



int main() {
    Solution s;
    vector<int> nums={5,4,-1,7,8};
    int a = s.maxSubArray(nums) ;
    cout << 2;
    return 0;
}
