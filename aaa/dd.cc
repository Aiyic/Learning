#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  int m;
  cin >> n >> m;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  int left;
  while (left < n && a[left] >= m) {
    left++;
  }
  if (left == n) {
    cout << 0 << endl;
    return 0;
  }
  int right = left + 1;
  int now_m = a[left];
  int max_len = 1;
  int now_len = 1;
  while (right < n) {
    if (now_m + a[right] > m) {
      max_len = max(now_len, max_len);
      now_m -= a[left];
      left++;
      now_len--;
    } else {
      now_m += a[right];
      right++;
      now_len++;
    }
  }
  max_len = max(now_len, max_len);
  cout << max_len << endl;
  return 0;
}

/*

5 5
1 4 2 2 1

*/