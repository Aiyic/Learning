
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int n=nums.size();
        int left=0,right=n,mid;
        while(left<right){
            mid=left+(right-left)/2;
            if(nums[mid]<target) left=mid+1;
            else if(nums[mid]>target) right=mid;
            else return mid;
        }
        return -1;
    }
};

int main() {
    Solution s;
    vector<int> nums = {-1,0,3,5,9,12};
    auto a = s.search(nums, 9) ;
    cout << a;
    return 0;
}
