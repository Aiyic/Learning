#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  static int maxProfit(vector<int> &prices) {
    int n = prices.size();
    vector<array<array<int, 2>, 3>> dp(n);

    // dp[i][nums][0/1]到第i天，交易nums次（购买），持有（不能同时持有2支）或不持有股票的最大收益
    dp[0][0][0] = 0;
    dp[0][1][1] = -prices[0];
    dp[0][2][1] = -prices[0];

    for (int i = 1; i < n; ++i) {
      // 从没买过
      // dp[i][0][0]
      // 买了0次但持有？
      // dp[i][0][1]

      // 买过一次，当前未持有，来自1.以前卖出，2.本次卖出
      dp[i][1][0] = max(dp[i - 1][1][0], dp[i - 1][1][1] + prices[i]);
      // 买过一次，当前持有，来自1.以前买的，2.本次买的
      dp[i][1][1] = max(dp[i - 1][1][1], dp[i - 1][0][0] - prices[i]);

      // 买过两次，当前未持有，本次来自1.以前已卖出两次，2.本次卖出第二次
      dp[i][2][0] = max(dp[i - 1][2][0], dp[i - 1][2][1] + prices[i]);
      // 买过两次，当前持有，本次来自1.以前已买过两次，2.本次买的第二次
      dp[i][2][1] = max(dp[i - 1][2][1], dp[i - 1][1][0] - prices[i]);
    }

    return max({
      dp[n-1][0][0],
      dp[n-1][0][1],
      dp[n-1][1][0],
      dp[n-1][1][1],
      dp[n-1][2][0],
      dp[n-1][2][1]
    });
  }
};

int main() {
  vector<int> prices = {1,2,3,4,5};
  auto a = Solution::maxProfit(prices);
  cout << 1;
  return 0;
}
