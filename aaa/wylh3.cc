
#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  int x;
  int y;
  int zuanshi;
  int jinengshu;
  cin >> n >> x >> y >> zuanshi >> jinengshu;

  vector<unordered_set<int>> next_ab(n + 1);
  vector<unordered_set<int>> parent(n + 1);

  for (int i = 2; i <= n; ++i) {
    int p;
    cin >> p;
    next_ab[p].insert(i);
    parent[i].insert(p);
  }
  vector<int> t(n + 1);
  vector<int> a(n + 1);
  vector<int> b(n + 1);
  for (int i = 1; i <= n; ++i) {
    cin >> t[i] >> a[i] >> b[i];
  }

  int ab = 1;
  int maxab = 1;
  unordered_set<int> visit;
  visit.insert(1);
  auto can_learn = [&](int now) {
    for (int i : parent[now]) {
      if (visit.find(i) == visit.end()) {
        return false;
      }
    }
    return true;
  };
  function<void(int)> back = [&](int now) {
    if (t[now] == 0) {
      if (zuanshi >= x * a[now]) {
        zuanshi -= x * a[now];
        ab += b[now];
        maxab = max(maxab, ab);
        for (auto next : next_ab[now]) {
          if (can_learn(next)) {
            back(next);
          }
        }
        zuanshi += x * a[now];
        ab -= b[now];
      }
    } else {
      if (zuanshi >= y * a[now]) {
        zuanshi -= y * a[now];
        ab += b[now];
        maxab = max(maxab, ab);
        for (auto next : next_ab[now]) {
          if (can_learn(next)) {
            back(next);
          }
        }
        zuanshi += y * a[now];
        ab -= b[now];
      }
      if (jinengshu >= a[now]) {
        jinengshu -= a[now];
        ab += b[now];
        maxab = max(maxab, ab);
        for (auto next : next_ab[now]) {
          if (can_learn(next)) {
            back(next);
          }
        }
        jinengshu += x * a[now];
        ab += b[now];
      }
    }
  };
  back(1);
  cout << maxab << endl;
  return 0;
}

/*

5
1 2
7 3
1 2 1 2
0 2 1
1 3 2
0 1 1
0 5 6
0 2 5

*/