#include<iostream>
#include<vector>
#include<stack>
#include<functional>
#include<algorithm>

using namespace std;

class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int n = nums.size();
        int flag=0,i;
        int minnum=INT_MIN;
        for(i=n-1; i>=0; i--){
            if(nums[i]>=minnum){
                minnum = nums[i];
                continue;
            }
            else{
                flag=1;
                break;
            }
        }
        if(flag){
            sort(nums.begin()+i+1,nums.end());
            for(int j=i+1; j<n; j++){
                if(nums[i]<nums[j]){
                    swap(nums[i],nums[j]);
                    break;
                }
            }
        }
        else
            sort(nums.begin(),nums.end());
    }
};

int main() {
    Solution x;
    vector<int> nums;
    nums.push_back(2);
    nums.push_back(3);
    nums.push_back(1);
    x.nextPermutation(nums);
    return 0;
}
