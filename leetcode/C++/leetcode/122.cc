#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    static int maxProfit(vector<int>& prices) {
      int n = prices.size();
      vector<array<int, 2>> dp(n);
      dp[0][0] = 0;
      dp[0][1] = -prices[0];

      for (int i=1; i<n; ++i) {
        dp[i][0] = max(dp[i-1][0], dp[i-1][1]+prices[i]);
        dp[i][1] = max(dp[i-1][1], dp[i-1][0]-prices[i]);
      }

      return max(dp[n-1][0], dp[n-1][1]+prices[n-1]);
    }
};

int main() {
  vector<int> prices = {7,1,5,3,6,4};
  auto a = Solution::maxProfit(prices);
  cout << 1;
  return 0;
}
