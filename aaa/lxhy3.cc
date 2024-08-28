#include <bits/stdc++.h>
using ll = long long;
using namespace std;

int main() {
  int n;
  int m;
  cin >> n >> m;
  vector<int> a(n);
  priority_queue<int, vector<int>, greater<>> que;

  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  for (int i = 0; i < m; ++i) {
    int x;
    cin >> x;
    que.push(x);
  }
  while (que.size() > n) {
    que.pop();
  }
  for (auto x : a) {
    que.push(x);
    if (que.size() > n) {
      que.pop();
    }
  }
  ll res = 0;
  while (!que.empty()) {
    res += que.top();
    que.pop();
  }
  cout << res << endl;
  return 0;
}

/*

4 1
6 2 1 1
5

*/