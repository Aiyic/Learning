#include <bits/stdc++.h>
#include <vector>

using namespace std;

int main() {
  int n;
  cin >> n;
  using ll = long long;
  int mod = 1e9 + 7;
  vector<ll> num(n);
  for (int i = 0; i < n; ++i) {
    cin >> num[i];
  }
  if (n % 2 != 0) {
    n--;
    for (int i = 0; i < n; i += 2) {
      num[i] = num[i] + num[i + 1];
      if (i + 1 < n) {
        num[i + 1] = num[i + 1] - num[i + 2];
      }
    }
  }
  while (n > 4) {
    n -= 4;
    for (int i = 0; i < n; ++i) {
      num[i] = num[i] + 2 * num[i + 2] + num[i + 4];
    }
  }
  vector<int> flag = {1, -1, -1, 1};
  int idx = 0;
  while (n > 1) {
    n--;
    for (int i = 0; i < n; i += 2) {
      num[i] = num[i] + flag[idx] * num[i + 1];
      if (i + 1 < n) {
        num[i + 1] = num[i + 1] - flag[idx] * num[i + 2];
      }
    }
    idx++;
  }
  cout << num[0] % mod << endl;
  return 0;
}

/*

4
1 2 3 4


*/