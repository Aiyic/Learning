#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    double findMaxAverage(vector<int>& nums, int k) {
        int sum = 0;
        int n = nums.size();
        for (int i = 0; i < k; i++) {
            sum += nums[i];
        }
        int maxSum = sum;
        for (int i = k; i < n; i++) {
            sum = sum - nums[i - k] + nums[i];
            maxSum = max(maxSum, sum);
        }
        return (double)maxSum / k;
    }
};

int main() {
    Solution s;
    vector<int> nums={7,4,5,8,8,3,9,8,7,6};
    double a = s.findMaxAverage(nums,7) ;
    cout << 1;
    return 0;
}
