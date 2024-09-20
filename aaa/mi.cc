#include <bits/stdc++.h>
using namespace std;

int main() {
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    vector<int> a(n);
    vector<int> b(n);
    for (int i = 0; i < n; ++i) {
      cin >> a[i];
    }
    for (int i = 0; i < n; ++i) {
      cin >> b[i];
    }
    auto judge = 
        [&](const vector<int> &a, const vector<int> &b) -> bool {
      int last = min(a[0], b[0]);
      for (int i = 1; i < n; ++i) {
        if (last > a[i] && last > b[i]) {
          return false;
        }
        if (last > a[i]) {
          last = b[i];
        } else if (last > b[i]) {
          last = a[i];
        } else {
          last = min(a[i], b[i]);
        }
      }
      return true;
    };
    if (judge(a, b) || judge(b, a)) {
      cout << "YES" << endl;
    } else {
      reverse(a.begin(), a.end());
      reverse(b.begin(), b.end());
      if (judge(a, b) || judge(b, a)) {
        cout << "YES" << endl;
      } else {
        cout << "NO" << endl;
      }
    }
  }
  return 0;
}

/*

2
5
1 3 5 2 4
5 2 3 4 1
7
1 2 3 4 3 2 1
4 3 2 1 2 3 4

*/