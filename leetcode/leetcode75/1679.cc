#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxOperations(vector<int>& nums, int k) {
        sort(nums.begin(),nums.end());
        int i=0,j=nums.size()-1,res=0;
        while(i<j){
            if(nums[i]+nums[j]>k){
                j--;
            }
            else if(nums[i]+nums[j]<k){
                i++;
            }
            else{
                i++;
                j--;
                res++;
            }
        }
        return res;
    }
};

int main() {
    Solution s;
    vector<int> nums = {3,1,3,4,3};
    int a = s.maxOperations(nums,6) ;
    cout << 1;
    return 0;
}
