#include <algorithm>
#include <bits/stdc++.h>
#include <utility>
using namespace std;

int main() {
  int n;
  cin >> n;
  vector<int> x(n);
  for (int i = 0; i < n; ++i) {
    cin >> x[i];
  }
  if (n == 1) {
    cout << x[0];
  } else if (n == 2) {
    cout << max(x[0], x[0]) << ' ' << min(x[0], x[0]);
  } else {
    unordered_map<int, int> count;
    int i = 0;
    while (i < n - 2) {
      int &a = x[i];
      int &b = x[i + 1];
      int &c = x[i + 2];
      if (count[b] < 2 && count[c] < 2) {
        if (b < c) {
          swap(b, c);
          count[b]++;
          count[c]++;
        }
      }
      if (count[a] < 2 && count[b] < 2) {
        if (a < b) {
          swap(a, b);
          count[a]++;
          count[b]++;
        }
      }
      i++;
    }
    int &b = x[n - 2];
    int &c = x[n - 1];
    if (count[b] < 2 && count[c] < 2 && b < c) {
      swap(b, c);
    }
    for_each(x.begin(), x.end(), [](int i) { cout << i << ' '; });
  }
  return 0;
}
/*

8
3 7 2 1 6 5 4 8
7 3 6 5 2 1 8 4

*/