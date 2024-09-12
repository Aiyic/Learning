#include <bits/stdc++.h>

using namespace std;

int main() {
  int n;
  int q;
  cin >> n >> q;
  vector<int> a(n);
  multimap<int, int> a_r;
  int count = 0;
  int total = 0;
  for (int i = 0; i < n; ++i) {
    int tmp;
    cin >> tmp;
    total += tmp;
    a[i] = tmp;
    a_r.insert({tmp, i});
    if (tmp == 1 || tmp == 0) {
      count++;
    }
  }
  auto fun = [&]() {
    if (total <= 2 || a_r.size() == 1) {
      return -1;
    }
    auto &[k, v] = *a_r.rbegin();
    if (count >= a_r.size() - 1) {
      return k - 1;
    }
    return k;
  };
  cout << fun() << endl;
  for (int loop = 0; loop < q; ++loop) {
    int l;
    int r;
    int x;
    char c;
    cin >> c >> l >> r >> x;
    if (c == '-') {
      x = -x;
    }
    for (int i = l-1; i <= r-1; ++i) {
      int v = a[i];
      auto range = a_r.equal_range(v);
      auto it = range.first;
      for (; it != range.second; ++it) {
        if (it->first == v && it->second == i) {
          break;
        }
      }
      int k = it->second;
      a_r.erase(it);
      a[i] += x;
      total += x;
      if (v <= 1 && a[i] > 1) {
        count--;
      } else if (v > 1 && a[i] <= 1) {
        count++;
      }
      a_r.insert({a[i], i});
    }
    cout << fun() << endl;
  }
  return 0;
}

/*

2 3
1 1
+ 2 2 1
+ 2 2 1
+ 1 1 1

2 1
1 1
+ 2 2 1

3 1
3 4 5
- 1 2 3

*/