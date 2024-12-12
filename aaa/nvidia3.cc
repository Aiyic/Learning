#include <algorithm>
#include <bits/stdc++.h>
#include <iterator>
#include <vector>
using namespace std;

int main() {
  int n;
  int a;
  int b;
  cin >> n >> a >> b;
  vector<int> L(n);
  vector<int> H(n);

  for (int i = 0; i < n; ++i) {
    cin >> L[i] >> H[i];
  }
  vector<vector<vector<int>>> dp(
      n + 1, vector<vector<int>>(a + 1, vector<int>(b + 1, INT_MAX)));
  dp[0][0][0] = 0;
  dp[0][1][0] = L[0];
  dp[0][0][1] = H[0];
  for (int day = 1; day <= n; ++day) {
    for (int i = 0; i <= a; ++i) {
      for (int j = 0; j <= b; ++j) {
        vector<int> nums = {dp[day - 1][i][j]};
        if (i > 0) {
          nums.push_back(dp[day - 1][i - 1][j] + L[day]);
        }
        if (j > 0) {
          nums.push_back(dp[day - 1][i][j - 1] + H[day]);
        }
        if (i + j > day + 1)
          continue;
        dp[day][i][j] = *min_element(nums.begin(), nums.end());
      }
    }
  }
  cout << dp[n][a][b] << endl;
  return 0;
}

/*

6 3 2
5 2
6 4
7 5
1 10
2 3
1 1


*/