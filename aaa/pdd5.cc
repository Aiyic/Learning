#include <bits/stdc++.h>
using namespace std;

int main() {
  int t;
  cin >> t;
  while (t--) {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
      cin >> a[i];
    }
    multiset<int> sort_nums;
    int last_insert = 0;
    int count = 0;
    for (int x : a) {
      auto it = sort_nums.insert(x);
      if (it == sort_nums.begin() || *prev(it) != last_insert) {
        count++;
      }
      last_insert = x;
    }
    if (count > k) {
      cout << "false" << endl;
    } else {
      cout << "true" << endl;
    }
  }
  return 0;
}

/*

3
5 3
8 12 7 -6 5
4 2
2 3 -6 4
5 5
10 6 8 -5 -10

*/