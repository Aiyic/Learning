#include <bits/stdc++.h>
#include <vector>

using namespace std;

int main() {
  int m, n;
  cin >> m >> n;
  vector<vector<bool>> arr(m, vector<bool>(n, false));
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      char c;
      cin >> c;
      arr[i][j] = (c == 'Y');
    }
  }

  vector<vector<vector<int>>> dp(m, vector<vector<int>>(n, vector<int>(4, 0)));
  dp[0][0][1] = (arr[0][0] ? 1 : 0);
  dp[0][0][3] = dp[0][0][1];
  for (int i = 1; i < m; ++i) {
    if (arr[i][0]) {
      dp[i][0][1] = 1;
      if (i > 0 && dp[i - 1][0][1] == 1) {
        dp[i][0][3] = 1;
      }
    } else if (i > 0 && dp[i - 1][0][1] == 1) {
      dp[i][0][2] = 1;
    }
  }

  for (int j = 1; j < n; ++j) {
    for (int i = 0; i < m; ++i) {
      dp[i][j][0] = max({dp[i][j-1][0], dp[i][j-1][1], dp[i][j-1][2], dp[i][j-1][3]});
      dp[i][j][1] = dp[i][j-1][0] + 1;
      dp[i][j][2] = max(dp[i][j-1][00], dp[i][j-1][01]);
      dp[i][j][3] = dp[i][j-1][0] + 1;
    }
  }

  int res = 0;
  for (int i = 0; i < m; ++i) {
    res += max(
        {dp[i][n - 1][0], dp[i][n - 1][1], dp[i][n - 1][2], dp[i][n - 1][3]});
  }
  cout << res << endl;
  return 0;
}

/*

dp[i][j][00/01/10/11] 每行 当前位置和上个位置 有人/没人 能坐下的最多人数

dp[i][j-1][00/01/10/11]  dp[i-1][j-1][00/01/10/11]

dp[i][j][00] = max(dp[i][j])
dp[i][j][01] = dp[i][j][00]+1
dp[i][j][10] = max(dp[i][j][00], dp[i][j][01])   //
max(dp[i-1][j][01]-dp[i-1][j][00], dp[i-1][j][11]-dp[i-1][j][10]) dp[i][j][11] =
dp[i][j][00]+1


3 6
X Y X X Y X
Y X X X X Y
X Y X X Y X


*/