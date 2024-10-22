// #include "../base/Node.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  static int fun(vector<int> nums, int a) {
    int n = nums.size();
    int res = 0;
    while ((a--) != 0) {
      if (nums.empty())
        break;
      vector<int> nums2;
      for (int i = 1; i < nums.size() - 1; ++i) {
        nums2.push_back(nums[i - 1] + nums[i] + nums[i + 1]);
      }
      auto max = ranges::max_element(nums2);
      res += *max;
      int d = distance(nums2.begin(), max);
      nums.erase(next(nums.begin(), d), next(nums.begin(), d + 3));
    }
    return res;
  }
};

int main() {

  auto a = Solution::fun({1, 2, 3, 1, 1, 2, 3}, 2);
  cout << 1;
  return 0;
}

/*

1, 1, 2, 3

 

*/