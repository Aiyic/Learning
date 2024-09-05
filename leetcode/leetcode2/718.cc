#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
#define ONE_DIM
#ifndef ONE_DIM
  static int findLength(vector<int> &nums1, vector<int> &nums2) {
    int n = nums1.size();
    int m = nums2.size();
    vector<vector<int>> dp(n, vector<int>(m, 0));
    // dp[n-1][m-1]=int(nums1[n-1]==nums2[m-1])
    // dp[i][j] = dp[i-1][j-1]+1  if(nums1[i]==nums2[j])
    dp[0][0] = static_cast<int>(nums1[0] == nums2[0]);
    int res = 0;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (i == 0) {
          dp[0][j] = static_cast<int>(nums1[0] == nums2[j]);
        } else if (j == 0) {
          dp[i][0] = static_cast<int>(nums1[i] == nums2[0]);
        } else if (nums1[i] == nums2[j]) {
          dp[i][j] = dp[i - 1][j - 1] + 1;
        }
        res = max(res, dp[i][j]);
      }
    }
    return res;
  }

#else
  static int findLength(vector<int> &nums1, vector<int> &nums2) {
    int n = nums1.size();
    int m = nums2.size();
    vector<int> dp(m, 0);
    dp[0] = static_cast<int>(nums1[0] == nums2[0]);
    for (int j = 0; j < m; ++j) {
      dp[j] = static_cast<int>(nums1[0] == nums2[j]);
    }
    int res = *max_element(dp.begin(), dp.end());
    for (int i = 1; i < n; ++i) {
      for (int j = m - 1; j >= 0; --j) {
        if (j == 0) {
          dp[0] = static_cast<int>(nums1[i] == nums2[0]);
        } else if (nums1[i] == nums2[j]) {
          dp[j] = dp[j - 1] + 1;
        } else {
          dp[j] = 0;
        }
        res = max(res, dp[j]);
      }
    }
    return res;
  }
#endif // ONE_DIM
};

int main() {
  vector<int> nums1 = {1, 0, 0, 0, 1, 0, 0, 1, 0, 0};
  vector<int> nums2 = {0, 1, 1, 1, 0, 1, 1, 1, 0, 0};
  auto a = Solution::findLength(nums1, nums2);
  cout << a;
  return 0;
}
