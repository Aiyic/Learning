#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  int m;
  int k;
  cin >> n >> m >> k;
  vector<unordered_map<int, int>> edge(n + 1);
  for (int i = 0; i < m; ++i) {
    int u;
    int v;
    int w;
    cin >> u >> v >> w;
    edge[u].insert({v, w});
    edge[v].insert({u, w});
  }
  vector<int> dist(n + 1, INT_MAX);
  set<pair<int, int>> min_heap;
  dist[1] = 0;
  min_heap.insert({0, 1});
  while (!min_heap.empty()) {
    int u = min_heap.begin()->second;
    min_heap.erase(min_heap.begin());
    for (auto [v, w] : edge[u]) {
      int new_dist = dist[u] + w;
      if (new_dist < dist[v]) {
        min_heap.erase({dist[v], v});
        dist[v] = new_dist;
        min_heap.insert({new_dist, v});
      }
    }
  }
  int res = 0;
  for (int i = 0; i < k; ++i) {
    int p, len;
    cin >> p >> len;
    if (dist[p] <= len) {
      res++;
    }
  }
  cout << res << endl;
  return 0;
}

/*

2 2 2
1 2 2
2 1 3
2 2
2 3


7 9 0
1 2 2
1 3 6
2 4 5
3 4 8
4 6 15
4 5 10
5 6 6
5 7 2
6 7 6

0 2 6 7 17 22 19
*/