
#include <bits/stdc++.h>
#include <functional>
#include <unordered_set>
#include <vector>

using namespace std;

int main() {
  int n, m, t;
  cin >> n >> m >> t;
  vector<unordered_set<int>> edge(n);
  vector<unordered_set<int>*> can_go_set(n);

  for (int i = 0; i < m; ++i) {
    int a, b, c;
    cin >> a >> b >> c;
    edge[a].insert(b);
    edge[a].insert(c);
    edge[b].insert(a);
    edge[b].insert(c);
    edge[c].insert(a);
    edge[c].insert(b);
  }

  auto is_nerber = [&](int i, int j) {
    return edge[i].find(j) != edge[i].end();
  };
  vector<bool> visit(n, false);
  vector<bool> total_visit(n, false);

  function<void(int, int)> can_go = [&](int root, int now) {
    if (!visit[now]) {
      visit[now] = true;
      can_go_set[root]->insert(now);
      for (int next : edge[now]) {
        can_go(root, next);
      }
    }
  };

  for (int i = 0; i < n; ++i) {
    if(total_visit[i]) continue;
    can_go_set[i] = new unordered_set<int>;
    total_visit[i]=true;
    visit.clear();
    visit.resize(n, false);
    can_go(i, i);
    for(int j:*can_go_set[i]){
      total_visit[j]=true;
      can_go_set[j]=can_go_set[i];
    }
  }

  for (int i = 0; i < t; ++i) {
    int a, b;
    cin >> a >> b;
    if (is_nerber(a, b)) {
      cout << 1 << endl;
    } else {
      if (can_go_set[a]->find(b) != can_go_set[a]->end()) {
        cout << 2 << endl;
      } else {
        cout << 3 << endl;
      }
    }
  }

  return 0;
}

/*

9 4 5
0 1 2
0 2 3
3 2 4
5 6 7
0 1
1 4
3 6
5 7
6 8

*/