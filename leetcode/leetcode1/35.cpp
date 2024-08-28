#include<iostream>
#include<vector>
#include<stack>
#include<functional>
#include<algorithm>

using namespace std;

class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int l=0,r=nums.size()-1,m;
        while(l<r){
            m=l+(r-l)/2;
            if(nums[m]==target) break;
            else if(nums[m]<target) l=m+1;
            else if(nums[m]>target) r=m-1;
        }
        m=l+(r-l)/2;
        if(nums[m]==target) return m;
        else{
            if(nums[m]>target) return l;
            else return l+1;
        } 
    }
};

int main() {
    Solution x;
    vector<int> nums = {1,3,5,6};
    int a = x.searchInsert(nums,2);
    cout << 1;
    return 0;
}
