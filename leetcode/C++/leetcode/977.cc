
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        vector<int> res;
        int i=0,j=nums.size()-1;
        while (i<=j)
        {
            if(nums[i]+nums[j]>=0){
                res.emplace_back(nums[j]*nums[j]);
                j--;
            }
            else{
                res.emplace_back(nums[i]*nums[i]);
                i++;
            }
        }
        reverse(res.begin(),res.end());
        return res;
    }
};

int main() {
    Solution s;
    vector<int> nums = {-4,-1,0,3,10};
    auto a = s.sortedSquares(nums) ;
    cout << 1;
    return 0;
}
