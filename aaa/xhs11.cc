#include <bits/stdc++.h>
#include <functional>
#include <vector>

using namespace std;

int main() {
  int n;
  cin >> n;
  set<int> ab;
  int sum = 0;
  for (int i = 0; i < n; ++i) {
    int x;
    cin >> x;
    sum += x;
    ab.insert(x);
  }
  double half = 0.5 * sum;
  // dp[i][half]
  vector<int> a(ab.rbegin(), ab.rend());
  int nowsum = 0;
  double mindiff = 1e6 * 2;
  int res = 0;
  vector<int> last(n);
  int total = sum;
  for (int i = 0; i < n; ++i) {
    last[i] = total;
    total -= a[i];
  }
  function<void(int)> back = [&](int idx) {
    if (idx >= n)
      return;
    if (nowsum - half >= mindiff)
      return;
    if (abs(sum - 2*(nowsum+)) >= mindiff)
      return;
    if (abs(sum - 2*nowsum) < mindiff) {
      mindiff = abs(sum - 2*nowsum);
      res = nowsum;
    }
    nowsum += a[idx];
    back(idx + 1);
    nowsum -= a[idx];
    back(idx + 1);
  };
  back(0);
  cout << abs(sum - 2 * res) << endl;
  return 0;
}

/*

4
7 4 5 3

*/