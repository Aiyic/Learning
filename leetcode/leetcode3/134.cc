// #include "../base/Node.h"
#include <bits/stdc++.h>
#include <csignal>
#include <vector>

using namespace std;

class Solution {
public:
  static int canCompleteCircuit(vector<int> &gas, vector<int> &cost) {
    int n = gas.size();

    int all_gas = 0;
    int all_cost = 0;
    for_each(gas.begin(), gas.end(), [&all_gas](int g) { all_gas += g; });
    for_each(cost.begin(), cost.end(), [&all_cost](int c) { all_cost += c; });
    if (all_gas < all_cost) {
      return -1;
    }

    vector<int> dp(n);
    dp[0] = gas[0] - cost[0];
    int min_idx = 0;
    for (int i = 1; i < n; ++i) {
        dp[i] = dp[i - 1] + gas[i] - cost[i];
        if (dp[i] < dp[min_idx]) {
            min_idx = i;
        }
    }
    return (min_idx + 1) % n;
  }
};

int main() {
  vector<int> gas = {1, 2, 3, 4, 5};
  vector<int> cost = {3, 4, 5, 1, 2};

  auto a = Solution::canCompleteCircuit(gas, cost);
  cout << 1;
  return 0;
}

/*

~

*/
