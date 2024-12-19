#include <iostream>
#include <vector>

const int MOD = 1e9 + 7;

// 计算不同字符串数量
long long countDifferentStrings(int n, int m) {
  // dp[i][j][k]表示前i个字符进行了j次操作，且当前字符操作k次的组合数
  std::vector<std::vector<std::vector<long long>>> dp(
      n + 1,
      std::vector<std::vector<long long>>(m + 1, std::vector<long long>(3, 0)));

  // 初始化状态
  dp[0][0][0] = 1; // 0个字符，0次操作，只有1种情况（空字符串）

  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j <= m; ++j) {
      // k = 0: 当前字符保持为 'a'
      dp[i][j][0] = dp[i - 1][j][0]; // 前i-1个字符保持不变
      if (j > 0) {
        dp[i][j][0] =
            (dp[i][j][0] + dp[i - 1][j - 1][1]) % MOD; // 前i-1个字符经过1次操作
        dp[i][j][0] = (dp[i][j][0] + dp[i - 1][j - 1][2]) %
                      MOD; // 前i-1个字符经过2次及以上操作
      }

      // k = 1: 当前字符经过1次替换
      if (j > 0) {
        dp[i][j][1] = (dp[i][j][1] + dp[i - 1][j - 1][0] * 25) %
                      MOD; // 前i-1个字符保持为 'a'
        dp[i][j][1] = (dp[i][j][1] + dp[i - 1][j - 1][1] * 25) %
                      MOD; // 前i-1个字符经过1次替换
        dp[i][j][1] = (dp[i][j][1] + dp[i - 1][j - 1][2] * 25) %
                      MOD; // 前i-1个字符经过2次及以上替换
      }

      // k = 2: 当前字符经过2次或更多次替换
      if (j > 0) {
        dp[i][j][2] = (dp[i][j][2] + dp[i - 1][j - 1][0] * 26) %
                      MOD; // 前i-1个字符保持为 'a'
        dp[i][j][2] = (dp[i][j][2] + dp[i - 1][j - 1][1] * 26) %
                      MOD; // 前i-1个字符经过1次替换
        dp[i][j][2] = (dp[i][j][2] + dp[i - 1][j - 1][2] * 26) %
                      MOD; // 前i-1个字符经过2次及以上替换
      }
    }
  }

  // 计算总结果
  long long total = 0;
  for (int k = 0; k < 3; ++k) {
    total = (total + dp[n][m][k]) % MOD;
  }

  return total;
}

int main() {

  int n, m;
  std::cin >> n >> m;

  long long result = countDifferentStrings(n, m);
  std::cout << result << std::endl; // 输出结果

  return 0;
}