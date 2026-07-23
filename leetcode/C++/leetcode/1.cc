// #include "../base/Node.h"
#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;

/*
 * @lc app=leetcode.cn id=1 lang=cpp
 *
 * [1] 两数之和
 */

// @lc code=start
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> m;
        for (int i=0; i<nums.size(); i++){
            auto it = m.find(nums[i]);
            if(it != m.end()){
                return {i, it->second};
            }
            m.insert({target-nums[i], i});
        }
        return {};
    }
};
// @lc code=end

int main() {
    Solution s;
//   vector<int> arr= {1,2,3,4,4};
//   string s = "hello world";
    vector<int> arr= {3,2,4};
  auto a = s.twoSum(arr, 6);
  cout << 1;
  return 0;
}

/*

~

*/
