#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  int m;
  int q;
  cin >> n >> m >> q;
  vector<int> u(m);
  vector<unordered_set<int>> edge(n+1);
  for (int i = 0; i < m; ++i) {
    cin >> u[i];
  }
  for (int i = 0; i < m; ++i) {
    int v;
    cin >> v;
    edge[u[i]].insert(v);
  }

  vector<int> path;
  vector<int> dp(n + 1, -1);
  function<int(int)> back = [&](int now) {
    if (dp[now] == -1) {
      path.push_back(now);
      if (edge[now].empty()) {
        return 1;
      }
      int res = 0;
      for (int next : edge[now]) {
        res += back(next);
      }
      dp[now] = res;
    }
    return dp[now];
  };
  for (int i = 0; i < q; ++i) {
    int a;
    cin >> a;
    path.clear();
    cout << back(a) << ' ';
  }
  cout << endl;
  return 0;
}

/*

3 2 3
1 1
2 3
1 2 3

*/