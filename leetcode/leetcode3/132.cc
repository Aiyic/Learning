// #include "../base/Node.h"
#include <bits/stdc++.h>
#include <string_view>
#include <vector>
using namespace std;

class Solution {
public:
  static int minCut(string s) {
    int n = s.length();
    vector<int> dp(n + 1);

    auto judge = [](string_view s) {
      int i = 0;
      int j = s.length() - 1;
      while (i < j) {
        if (s[i++] != s[j--]) {
          return false;
        }
      }
      return true;
    };
    dp[0] = 1;
    int now = 0;
    int idx = 1;
    while (now + dp[idx-1] < n) {
      auto start = s.begin() + now;
      auto end = start + dp[idx - 1];
      string_view sub(start, end + 1);

      if (idx >= 2) {
        int last = now - 1;
        int next = now + dp[idx - 1];
        if (s[last] == s[next]) {
          dp[idx - 2]--;
          if (dp[idx - 2] == 0) {
            dp[idx - 2] = dp[idx - 1] + 2;
            dp[idx - 1] = 0;
            idx--;
          } else {
            dp[idx - 1] += 2;
          }
          now--;
          continue;
        }
      }

      if (judge(sub)) {
        dp[idx - 1]++;
        continue;
      }

      dp[idx] = 1;
      now += dp[idx - 1];
      idx++;
    }
    return idx - 1;
  }
};

int main() {
  // auto x = Solution::minCut("aab");
  // auto xx = Solution::minCut("a");
  // auto xxx = Solution::minCut("ab");
  // auto xxxx = Solution::minCut("abbab");
  // auto xxxx = Solution::minCut("aaabaa");
  auto xxxxx = Solution::minCut("cabababcbc");
  cout << 1;
  return 0;
}

/*

dp[i] s[0..i]的s[i]所在的回文子串长度


cabababcbc
c aba babcbc
c aba b a
c ab aba 

a aabaa
aaa b a
aa aba 
*/