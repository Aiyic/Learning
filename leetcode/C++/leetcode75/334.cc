#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool increasingTriplet(vector<int>& nums) {
        int n=nums.size();
        if(n<3) return false;
        vector<int> minnum(n),maxnum(n);
        int maxx=INT_MIN,minx=INT_MAX;
        for(int i=0;i<n;i++){
            if(nums[i]<minx)
                minx=nums[i];
            minnum[i]=minx;
        }
        for(int i=n-1;i>0;i--){
            if(nums[i]>maxx)
                maxx=nums[i];
            maxnum[i]=maxx;
        }
        for(int i=1;i<n-1;i++){
            if(minnum[i-1]<nums[i] && maxnum[i+1]>nums[i]) return true;
        }
        return false;
    }

    bool increasingTriplet2(const vector<int>& nums) {
        int first = INT_MAX;
        int second = INT_MAX;
        for (const auto& num : nums){
            if (num <= first) first = num;
            else if (num <= second) second = num;
            else return true;
        }
        return false;
    }
};

int main() {
    Solution s;
    vector<int> nums={1,2,3,4};
    bool a = s.increasingTriplet(nums) ;
    cout << 1;
    return 0;
}
