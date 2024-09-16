#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  int m;
  int t;
  cin >> n >> m >> t;
  unordered_map<int, unordered_set<int>> edge;
  for (int i = 0; i < m; ++i) {
    int u;
    int v;
    cin >> u >> v;
    edge[u].insert(v);
    edge[v].insert(u);
  }
  unordered_set<int> visit;
  unordered_set<int> now;
  unordered_set<int> next;
  set<int> result;
  for (int i = 0; i < t; ++i) {
    int a;
    cin >> a;
    now.insert(a);
  }
  while (!now.empty()) {
    auto it = now.begin();
    int x = *it;
    now.erase(it);
    visit.insert(x);
    bool flag = true;
    for (int nerber : edge[x]) {
      if (visit.find(nerber) == visit.end() && now.find(nerber) == now.end()) {
        next.insert(nerber);
        flag = false;
      }
    }
    if (flag) {
      result.insert(x);
    }
    if (now.empty() && !next.empty()) {
      now.swap(next);
    }
  }
  for (int x : result) {
    cout << x << ' ';
  }
  cout << endl;
  return 0;
}

/*

5 4 2
1 2
2 3
3 4
4 5
1 5


5 4 4
1 2
2 3
3 4
1 4
1 2 3 4



*/