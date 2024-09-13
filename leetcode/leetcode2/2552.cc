#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
  static const int kMax = 4001;
  using ll = int64_t;
  static ll countQuadruplets(vector<int> &nums) {
    int n = nums.size();
    ll res = 0;
    vector<vector<int>> dp_min_count(n, vector<int>(n + 1, 0));
    vector<vector<int>> dp_max_count(n, vector<int>(n + 1, 0));
    for (int x = 1; x <= n; ++x) {
      dp_min_count[0][x] = (nums[0] < x ? 1 : 0);
      for (int i = 1; i < n; ++i) {
        dp_min_count[i][x] = dp_min_count[i - 1][x];
        if (nums[i] < x) {
          dp_min_count[i][x]++;
        }
      }
    }
    for (int x = n; x >= 0; --x) {
      dp_max_count[n - 1][x] = (nums[n - 1] > x ? 1 : 0);
      for (int i = n - 2; i >= 0; --i) {
        dp_max_count[i][x] = dp_max_count[i + 1][x];
        if (nums[i] > x) {
          dp_max_count[i][x]++;
        }
      }
    }
    for (int j = 1; j < n - 2; ++j) {
      for (int k = j + 1; k < n - 1; ++k) {
        if (nums[j] > nums[k]) {
          ll max_count = dp_min_count[j-1][nums[k]];
          ll min_count = dp_max_count[k+1][nums[j]];
          res += max_count * min_count;
        }
      }
    }
    return res;
  }
};

int main() {
  vector<int> nums2 = {2,5,3,1,4};
  auto x = Solution::countQuadruplets(nums2);
  return 0;
}

/*


*/