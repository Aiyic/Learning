#include<iostream>
#include<vector>
#include<stack>
#include<functional>
#include<algorithm>

using namespace std;

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int n=nums.size();
        int l=0,r=n-1;
        int max=l;
        if(target==nums[n-1] || target==nums[0]){
            if(target==nums[n-1]) return n-1;
            else if(target==nums[0]) return 0;
            else return -1;
        }

        int mid=0;
        while(l<r){
            mid = (l+r)/2;
            if(mid==l) break;
            if(nums[mid]>nums[0]) l=mid; 
            else if(nums[mid]<nums[n-1]) r=mid;
        }
        max=l;
        if(nums[0]<nums[n-1]) max=n-1;
        
        if(target<nums[n-1]){
            l=(max+1)%n,r=n-1;
        } 
        else if(target>nums[0]){
            l=0;r=max;
        }

        while(l<r){
            mid = (l+r)/2;
            if(nums[mid]==target) return mid;
            else if(nums[mid]>target) r=mid;
            else if(nums[mid]<target) l=mid+1;
        }
        mid = (l+r)/2;
        if(nums[mid]==target) return mid;
        else return -1;
    }

    int search2(vector<int>& nums, int target) {
        int t = nums[0];
        int l = 0, r = nums.size() - 1;
        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (t > nums[mid]) r = mid - 1;
            else l = mid + 1;
        }

        if (target >= t) l = 0;
        else r = nums.size() - 1;
        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (target > nums[mid]) l = mid + 1;
            else if (target < nums[mid]) r = mid - 1;
            else return mid;
        }
        return -1;
    }
};

int main() {
    Solution x;
    vector<int> nums = {4,5,6,7,0,1,2};
    int a = x.search2(nums,0);
    cout << a;
    return 0;
}
