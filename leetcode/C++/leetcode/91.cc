
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

// dp[i] 代表s[0,i]的编码总数
// 如果i+1可编码
// dp[i+1] dp[i+2]

// s[0:2]可编码 = fun(s[1:]) + fun(s[2:])
class Solution {
public:
  map<string, int> dp;
  int numDecodings(string s) {
    if (s.length() == 0) {
      return 1;
    }
    if (s[0] == '0') {
      return 0;
    }
    if (s.length() == 1) {
      return 1;
    }
    auto it = dp.find(s);
    if (it != dp.end()) {
      return dp[s];
    }
    if (string(s, 0, 2) <= "26") {
      if (s[1] == '0') {
        dp[s] = numDecodings(string(s, 2));
      } else {
        dp[s] = numDecodings(string(s, 1)) + numDecodings(string(s, 2));
      }

    } else {
      dp[s] = numDecodings(string(s, 1));
    }
    return dp[s];
  }
};

int main() {
  Solution s;

  auto x = s.numDecodings("111111111111111111111111111111111111111111111");
  cout << 1;
  return 0;
}

/*

0 + list[]
1 + reverse[]

*/
