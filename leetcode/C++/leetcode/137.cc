// #include "../base/Node.h"
#include <bits/stdc++.h>
#include <cmath>
#include <cstdint>
#include <unordered_map>

using namespace std;

/*
 * @lc app=leetcode.cn id=137 lang=cpp
 *
 * [137] 只出现一次的数字 II
 */

// @lc code=start
class Solution {
public:
  static int singleNumber(vector<int>& nums) {
    int res = 0;
    for (int i=0 ; i < 32; i++){
      int bit = 0;
      for (int num: nums) {
        bit += (num >> i) & 1;
      }
      res += (bit % 3) << i;
    }

    return res;
  }

  static int singleNumber2(vector<int>& nums) {
    int a = 0;
    int b = 0;
    for (int num: nums) {
        b = ~a & (b ^ num);
        a = ~b & (a ^ num);
    }
    return b;
  }
};
// @lc code=end


int main() {
  vector<int> ratings = {0,1,0,1,0,1,99};

  auto a = Solution::singleNumber(ratings);
  cout << 1;
  return 0;
}
/*

1 1 2 1
x 1 2 1

*/
