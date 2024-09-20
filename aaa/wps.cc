#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cin >> n;
  vector<int> a(n + 1, 0);
  vector<int> value(n + 1, -1);
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }
  vector<unordered_set<int>> edge(n + 1);
  vector<int> parents(n+1,-1);
  for (int i = 0; i < n - 1; ++i) {
    int u;
    int v;
    cin >> u >> v;
    edge[u].insert(v);
    parents[v] = u;
  }
  function<int(int)> bfs = [&](int node) -> int {
    if (value[node] == -1) {
      int val = a[node];
      for (auto nerber : edge[node]) {
        val += bfs(nerber);
      }
      value[node] = val;
    }
    return value[node];
  };
  map<int, int> value_idx;
  for (int i = 1; i <= n; ++i) {
    value_idx[bfs(i)] = i;
  }
  auto is_child = [&](int i, int j) {
    if (i > j) {
      swap(i, j);
    }
    while(i < parents[j] ){
        j = parents[j];
    }
    return i == parents[j];
  };
  int min_diff = 1e9;
  for (auto it = value_idx.begin(); it != prev(value_idx.end()); ++it) {
    auto &[v, i] = *it;
    auto next_it = next(it);
    while (next_it != value_idx.end() && is_child(i, next_it->second)) {
      next_it = next(next_it);
    }
    if (next_it == value_idx.end()) {
      continue;
    }
    auto &[next_v, next_i] = *next_it;
    min_diff = min(min_diff,next_v-v);
  }
  cout << min_diff << endl;
  return 0;
}

/*

4
1 1 3 2
1 2
1 3
3 4



6
6 1 3 9 8 10
1 2
2 3
3 4
3 5
4 6


*/