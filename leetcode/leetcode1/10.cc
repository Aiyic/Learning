#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
  static bool isMatch(const string &s, const string &p) {
    int n = s.length();
    int m = p.length();
    vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));
    dp[0][0] = true;
    int i = 0;
    int j = 0;
    for (j = 1; j < m; j += 2) {
      if (p[j] == '*') {
        dp[0][j + 1] = dp[0][j - 1];
      }
    }
    for (i = 0; i < n; ++i) {
      for (j = 0; j < m; ++j) {
        if (p[j] == '.') {
          dp[i + 1][j + 1] = dp[i][j];
        } else if (p[j] == '*') {
          // a* = 0
          dp[i + 1][j + 1] = dp[i + 1][j - 1];
          char c = p[j - 1];
          if (s[i] == c || c == '.') {
            // a* = 1
            dp[i + 1][j + 1] = dp[i + 1][j + 1] || dp[i + 1][j];
            // a* > 1
            dp[i + 1][j + 1] = dp[i + 1][j + 1] || dp[i][j+1];
          } 
        } else {
          dp[i + 1][j + 1] = (dp[i][j] && s[i] == p[j]);
        }
      }
    }
    return dp[n][m];
  }
};

int main() {
  string s = "a";
  string p = ".*.";
  auto a = Solution::isMatch(s, p);
  cout << a;
  return 0;
}
