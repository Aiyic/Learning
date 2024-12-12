// #include "../base/Node.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  static int minCut(const string &s) {
    int n = s.length();
    vector<unordered_set<int>> lens(n);
    for (int i = 0; i < n; ++i) {
      int len = 0;
      while (i - len >= 0 && i + len < n && s[i - len] == s[i + len]) {
        len++;
        int idx = i + len - 1;
        lens[idx].insert(2 * len - 1);
      }
      if (i == n - 1) {
        continue;
      }
      len = 0;
      while (i - len >= 0 && i + 1 + len < n && s[i - len] == s[i + 1 + len]) {
        len++;
        int idx = i + len;
        lens[idx].insert(2 * len);
      }
    }
    vector<int> dp(n);
    for (int i = 0; i < n; ++i) {
      dp[i] = i;
    }
    for (int i = 1; i < n; ++i) {
      for (int len : lens[i]) {
        if (i - len >= 0) {
          dp[i] = min(dp[i], dp[i - len] + 1);
        } else {
          dp[i] = 0;
        }
      }
    }
    return dp[n - 1];
  }
};

int main() {
  auto x = Solution::minCut("abbabba");
  cout << 1;
  return 0;
}

/*

dp[i] s[0..i]回文子串数
      以s[i]结尾的最长回文子串长度

      以s[i]为对称点的最长回文子串长度
dp2[i] 以s[i..i+1]中间为对称点的最大子串长

dp[i+1]

aaabaa
aa b a
aba bb a
aa aba a
dp[i][j] s[0..i]

cabababcbc
c a babab cbc

bacab ababa

abba b




*/