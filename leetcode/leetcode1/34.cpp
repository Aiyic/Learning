#include<iostream>
#include<vector>
#include<stack>
#include<functional>
#include<algorithm>

using namespace std;

class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int l=0,r=nums.size()-1,m;
        while(l<r){
            m=l+(r-l)/2;
            if(nums[m]==target) break;
            else if(nums[m]<target) l=m+1;
            else if(nums[m]>target) r=m-1;
        }
        m=l+(r-l)/2;
        if(nums.size()==0) return vector<int>({-1,-1});
        else if(nums.size()==1){
            if(nums[0]==target) return vector<int>({0,0});
            else return vector<int>({-1,-1});
        }
        else{
            if(nums[m]!=target) return vector<int>({-1,-1});
        }
        int le=0,re=m;
        while(le<re){
            int me=le+(re-le)/2;
            if((double)nums[me]-(target-0.5)>0) re=me-1;
            else if((double)nums[me]-(target-0.5)<0) le=me+1;
        }
        int x=le;
        if(nums[x]<target) x++;

        le=m;
        re=nums.size()-1;
        while(le<re){
            int me=le+(re-le)/2;
            if((double)nums[me]-(target+0.5)<0) le=me+1;
            else if((double)nums[me]-(target+0.5)>0) re=me-1;
        }
        int y=re;
        if(nums[y]>target) y--;
        return vector<int>({x,y});
    }
};

int main() {
    Solution x;
    vector<int> nums = {1,2,3,3,3,3,4,5,9};
    vector<int> a = x.searchRange(nums,3);
    cout << 1;
    return 0;
}
