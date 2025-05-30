// 这类问题统一都是因为28行递归导致的栈溢出
// 总共有 m*n 种可能，而无缓冲的递归导致子问题重复计算
// 解决方案一：原思路上加个缓存，记录子问题答案
// 解决方案二：直接上 dp ...

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
  // static bool isInterleave2(const string &s1, const string &s2,
  //                           const string &s3) {
  //   // TODO(aiyic): bug
  //   vector<vector<int>> record(s1.length() + 1, vector<int>(s2.length() +
  //   1)); static function<bool(string_view, string_view, string_view)> fun =
  //       [&record](string_view s1, string_view s2, string_view s3) -> bool {
  //     if (s1.length() == 0) {
  //       return s2 == s3;
  //     }
  //     if (s2.length() == 0) {
  //       return s1 == s3;
  //     }
  //     if (record[s1.length()][s2.length()] != 0) {
  //       return record[s1.length()][s2.length()] == 1;
  //     }
  //     int idx = 0;
  //     while (idx < s1.length() && idx < s2.length() && s1[idx] == s3[idx] &&
  //            s2[idx] == s3[idx]) {
  //       idx++;
  //     }
  //     if (idx > 0 && (s1[idx] != s3[idx] && s2[idx] != s3[idx])) {
  //       record[s1.length()][s2.length()] =
  //           static_cast<int>(fun(s1.substr(idx), s2, s3.substr(idx)) ||
  //                            fun(s1, s2.substr(idx), s3.substr(idx)));
  //     }
  //     int idx1 = idx;
  //     if (s1[idx1] == s3[idx1]) {
  //       while (idx1 < s1.length() && s1[idx1] == s3[idx1]) {
  //         idx1++;
  //       }
  //       record[s1.length()][s2.length()] =
  //           static_cast<int>(fun(s1.substr(idx1), s2, s3.substr(idx1)));
  //     }
  //     int idx2 = idx;
  //     if (s2[idx2] == s3[idx2]) {
  //       while (idx2 < s2.length() && s2[idx2] == s3[idx2]) {
  //         idx2++;
  //       }
  //       record[s1.length()][s2.length()] =
  //           static_cast<int>(fun(s1, s2.substr(idx2), s3.substr(idx2)));
  //     }
  //     if (record[s1.length()][s2.length()] == 0) {
  //       record[s1.length()][s2.length()] = -1;
  //     }
  //     return record[s1.length()][s2.length()] == 1;
  //   };
  //   return fun(s1, s2, s3);
  // }

  static bool isInterleave2(const string &s1, const string &s2,
                            const string &s3) {
    if (s1.length() == 0) {
      return s2 == s3;
    }
    if (s2.length() == 0) {
      return s1 == s3;
    }
    if (s3.length() != s1.length() + s2.length()) {
      return false;
    }
    vector<vector<bool>> dp(s1.length() + 1, vector<bool>(s2.length() + 1));
    // dp[i][j] s1[:i+1] 和 s2[:j+1] 匹配 s3[:i+j+1]
    // dp[0][j] && dp[i][0]
    // dp[i][j] = (dp[i-1][j] && s1[i-1]==s3[i+j-1])
    //            || (dp[i][j-1] && s2[j-1]==s3[i+j-1])
    int i = 0;
    int j = 0;
    while (i < s1.length() && s1[i] == s3[i]) {
      dp[i + 1][0] = true;
      i++;
    }
    while (j < s2.length() && s2[j] == s3[j]) {
      dp[0][j + 1] = true;
      j++;
    }
    for (i = 1; i <= s1.length(); ++i) {
      for (j = 1; j <= s2.length(); ++j) {
        dp[i][j] = (i > 0 && (dp[i - 1][j] && s1[i - 1] == s3[i + j - 1])) ||
                   (j > 0 && (dp[i][j - 1] && s2[j - 1] == s3[i + j - 1]));
      }
    }
    return dp[s1.length()][s2.length()];
  }

  static bool isInterleave(const string &s1, const string &s2,
                           const string &s3) {
    if (s3.length() != s1.length() + s2.length()) {
      return false;
    }
    vector<bool> dp(s2.length() + 1);
    int i = 0;
    int j = 0;
    dp[0] = true;
    while (j < s2.length() && s2[j] == s3[j]) {
      dp[j + 1] = true;
      j++;
    }
    for (i = 1; i <= s1.length(); ++i) {
      for (j = s2.length(); j >= 0; --j) {
        if (dp[j]) {
          dp[j] = (s1[i - 1] == s3[i + j - 1]);
        }
      }
      for (j = 1; j <= s2.length(); ++j) {
        if (dp[j - 1]) {
          dp[j] = (dp[j] || (s2[j - 1] == s3[i + j - 1]));
        }
      }
    }
    return dp[s2.length()];
  }
};

int main() {
  // auto a = Solution::isInterleave(
  //     "bbbbbabbbbabaababaaaabbababbaaabbabbaaabaaaaababbbababbbbbabbbbababbabaa"
  //     "bababbbaabababababbbaaababaa",
  //     "babaaaabbababbbabbbbaabaabbaabbbbaabaaabaababaaaabaaabbaaabaaaabaabaabbb"
  //     "bbbbbbbbabaaabbababbabbabaab",
  //     "babbbabbbaaabbababbbbababaabbabaabaaabbbbabbbaaabbbaaaaabbbbaabbaaababab"
  //     "baaaaaabababbababaababbababbbababbbbaaaabaabbabbaaaaabbabbaaaabbbaabaaab"
  //     "aababaababbaaabbbbbabbbbaabbabaabbbbabaaabbababbabbabbab");
  auto a = Solution::isInterleave("aabcc", "dbbca", "aadbbcbcac");
  cout << 1;
  return 0;
}
