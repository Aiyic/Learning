#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cin >> n;
  vector<string> strs(n);
  set<pair<int, int>> idx;
  for (int i = 0; i < n; ++i) {
    cin >> strs[i];
  }

  for (int i = 1; i < n - 1; ++i) {
    for (int j = 1; j < n - 1; ++j) {
      char c = strs[i][j];
      if (c > strs[i + 1][j] && c > strs[i][j + 1] && c > strs[i - 1][j] &&
          c > strs[i][j - 1]) {
        idx.insert({i, j});
      }
    }
  }

  for (const auto &[i, j] : idx) {
    strs[i][j] = 'X';
  }
  for (auto &s : strs) {
    cout << s << endl;
  }
  return 0;
}

/*

4
1112
1912
1892
1234

*/