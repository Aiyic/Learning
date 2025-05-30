#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    void sortColors(vector<int>& nums) {
        int i=0,j=0;
        for(int idx=0;idx<nums.size();idx++){
            if(nums[idx]==0){
                swap(nums[idx],nums[i++]);
                if(i>j) j++;
                else swap(nums[idx],nums[j++]);
            }
            else if(nums[idx]==1){
                swap(nums[idx],nums[j++]);
            }
        }
    }
};


int main() {
    Solution solution;
    vector<int> matrix = {2,0,1};
    solution.sortColors(matrix) ;
    cout << 1;
    return 0;
}