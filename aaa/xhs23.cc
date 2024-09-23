#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int knapsack(int W, vector<int>& weights, vector<int>& values) {
    int n = weights.size();
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= W; j++) {
            if (weights[i - 1] > j) {
                dp[i][j] = dp[i - 1][j];
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - weights[i - 1]] + values[i - 1]);
            }
        }
    }

    return dp[n][W];
}

int main() {
    vector<int> weights = {9, 7, 8, 8, 3, 10, 10, 1};
    vector<int> values = {17, 17, 2, 2, 17, 13, 10, 2};
    int W = 18;

    int max_value = knapsack(W, weights, values);
    cout << "The maximum value that can be achieved is: " << max_value << endl;

    return 0;
}