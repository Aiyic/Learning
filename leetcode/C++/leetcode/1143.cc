#include <bits/stdc++.h>
#include <vector>

using namespace std;

class Solution {
public:
  static int longestCommonSubsequence(const string &text1,
                                      const string &text2) {
    int n = text1.size();
    int m = text2.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= m; ++j) {
        if (text1[i - 1] == text2[j - 1]) {
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
  string text1 = "bl";
  string text2 = "yby";
  auto a = Solution::longestCommonSubsequence(text1, text2);
  cout << a;
  return 0;
}
