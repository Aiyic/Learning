
#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
  int numTrees(int n) {
    static vector<int> dp(20);
    if (dp[n] != 0) {
      return dp[n];
    }
    if (n <= 1) {
      return 1;
    }
    int res = 0;
    for (int i = 1; i <= n; ++i) {
      res += numTrees(i - 1) * numTrees(n - i);
    }
    dp[n] = res;
    return dp[n];
  }
};

int main() {
  Solution s;

  auto a = s.numTrees(4);
  cout << 1;
  return 0;
}
