#include<bits/stdc++.h>
using namespace std;

class Solution {
public:

    int findKthLargest(vector<int>& nums, int k) {
        
        make_heap(nums.begin(),nums.end());
        
        for(int i=0; i<k-1; ++i){
            pop_heap(nums.begin(),nums.end()-i);
        }
        return nums[0];
    }

    // int findKthLargest(vector<int>& nums, int k) {
    //     nth_element(nums.begin(),nums.begin()+k-1,nums.end(), greater<int>());
    //     return nums[k-1];
    // }
};

int main() {
    Solution solution;
    vector<int> nums={3,2,1,5,6,4};
    auto a = solution.findKthLargest(nums,2);
    cout << 1;
    return 0;
}






