#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int i=0,j=0;
        while(i+j<nums.size()){
            if(nums[i+j]){
                swap(nums[i],nums[i+j]);
                i++;
            }
            else j++;
        }
    }
};

int main() {
    Solution s;
    vector<int> nums={0,1,0,3,12};
    s.moveZeroes(nums) ;
    cout << 1;
    return 0;
}
