
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

int main() {
  int n;
  int m;
  cin >> n >> m;
  vector<ll> f(n);
  vector<pair<ll, ll>> arr(m);
  for (int i = 0; i < n; ++i) {
    cin >> f[i];
  }
  for (int i = 0; i < m; ++i) {
    cin >> arr[i].first >> arr[i].second;
  }
  auto has_t = [&f](ll l, ll r) -> bool {
    vector<ll> ff(f.begin() + l, f.begin() + r);
    ranges::sort(ff);
    for (ll i = 0; i < ff.size() - 2; ++i) {
      if (ff[i] + ff[i + 1] > ff[i + 2]) {
        return true;
      }
    }
    return false;
  };
  for (auto &[i, j] : arr) {
    if (has_t(i-1, j)) {
      cout << 'Y';
    } else {
      cout << 'N';
    }
  }
  cout << endl;
  return 0;
}

/*

9 5
5
8
1
14
13
0
2
2
8
1 4
1 5
3 6
3 7
5 9


*/