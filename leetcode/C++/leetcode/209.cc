
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int i=0,j=0,n=nums.size();
        int m=INT_MAX,sum=nums[0];
        while (i<n) {
            while(sum<target){
                if(j==n-1) break;
                j++;
                sum+=nums[j];
            }
            if(sum<target) break; 
            m=min(m,j-i+1);
            sum-=nums[i];
            i++;
        }
        if(m==INT_MAX) return 0;
        else return m;
    }
};

int main() {
    Solution s;
    vector<int> nums = {2,3,1,2,4,3};
    auto a = s.minSubArrayLen(7, nums) ;
    cout << a;
    return 0;
}
