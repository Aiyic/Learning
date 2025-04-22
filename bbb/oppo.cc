#include <bits/stdc++.h>
using namespace std;

int countCombinations(int n) {
  // dp[i][j] 表示使用前 i 个数字，和 mod 3 为 j 的组合数量
  vector<vector<int>> dp(n + 1, vector<int>(3, 0));
  dp[0][0] = 1; // 0 个数字的和为 0（mod 3）

  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j < 3; ++j) {
      // 选择不加入当前数字
      dp[i][j] += dp[i - 1][j];

      // 选择加入当前数字
      dp[i][(j + 1) % 3] += dp[i - 1][j]; // 假设当前数字为 1
      dp[i][(j + 2) % 3] += dp[i - 1][j]; // 假设当前数字为 2
    }
  }

  return dp[n][0]; // 返回和 mod 3 为 0 的组合数量
}

int main() {
  int n;
  cin >> n;
  char a;
  cin >> a;

  vector<vector<int>> dp(n + 1, vector<int>(3, 0));
  if (a == '?') {
    dp[0][0] = 3;
    dp[0][1] = 3;
    dp[0][2] = 3;
  } else {
    dp[0][(a - '0') % 3] = 1;
  }

  for (int i = 1; i < n; i++) {
    cin >> a;
    if (a == '?') {
        dp[i][0] = (dp[i - 1][0] * 4 + dp[i - 1][1] * 3 + dp[i - 1][2] * 3) % 1000000007;
        dp[i][1] =( dp[i - 1][0] * 3 + dp[i - 1][1] * 4 + dp[i - 1][2] * 3) % 1000000007;
        dp[i][2] =( dp[i - 1][0] * 3 + dp[i - 1][1] * 3 + dp[i - 1][2] * 4) % 1000000007;
    } else {
        if((a-'0')%3 == 0) {
            dp[i][0] = dp[i - 1][0];
            dp[i][1] = dp[i - 1][1];
            dp[i][2] = dp[i - 1][2];
        } else if((a-'0')%3 == 1) {
            dp[i][0] = dp[i - 1][2];
            dp[i][1] = dp[i - 1][0];
            dp[i][2] = dp[i - 1][1];
        } else {
            dp[i][0] = dp[i - 1][1];
            dp[i][1] = dp[i - 1][2];
            dp[i][2] = dp[i - 1][0];
        }
    }
  }
  cout << dp[n-1][0] << '\n';
  return 0;
}

/*

3 6 9
12 21 03 30 
06 60 15 51 


*/