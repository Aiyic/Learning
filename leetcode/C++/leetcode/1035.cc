#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
  static int maxUncrossedLines(vector<int> &nums1, vector<int> &nums2) {
    int n = nums1.size();
    int m = nums2.size();

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    // dp[i][j] = dp[i-1][j-1]+1 if(nums[i]==nums[j])
    // dp[i][j] = max{dp[i-1][j], dp[i][j-1]}  if(nums[i]!=nums[j])
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= m; ++j) {
        if (nums1[i - 1] == nums2[j - 1]) {
          dp[i][j] = dp[i - 1][j - 1] + 1;
        } else {
          dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
      }
    }
    return dp[n][m];
  }
};

int main() {
  vector<int> nums1 = {2,5,1,2,5};
  vector<int> nums2 = {10,5,2,1,5,2};
  auto a = Solution::maxUncrossedLines(nums1, nums2);
  cout << a;
  return 0;
}
