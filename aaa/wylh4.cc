
#include <bits/stdc++.h>
#include <ranges>
using namespace std;

int main() {
  int n, m;
  cin >> n >> m;

  if (n == 1) {
    cout << 180 << "\n" << 1 << endl;
    return 0;
  }

  set<double> angle;
  for (int i = 0; i < n; ++i) {
    int p;
    cin >> p;
    angle.insert(p);
  }

  map<double, double> diff_angle;
  double last = *angle.begin();
  for (int i : angle) {
    if (i == last) {
      diff_angle.insert({i + 360 - *angle.rbegin(), *angle.rbegin()});
    } else {
      diff_angle.insert({i - last, last});
      last = i;
    }
  }

  auto fun = [&](int a) -> pair<double, double> {
    double diff_res = 0;
    for (auto [diff, start] : ranges::reverse_view(diff_angle)) {
      set<double> angle2;
      for (double i : angle) {
        if (i < start) {
          angle2.insert(360 + i - start);
        } else {
          angle2.insert(i - start);
        }
      }
      int node = 0;
      start = 0;
      while (start < 360) {
        auto it = angle2.lower_bound(start + diff);
        if (it != angle.end()) {
          start += diff;
          node++;
        } else {
          break;
        }
      }
      if (node >= a) {
        diff_res = diff;
        break;
      }
    }
    double kill = 0.5 / m + 0.5 / a - (180.0 - diff_res) / 360 / m / a;
    return {kill, diff_res};
  };
  double max_kill = 0;
  double max_diff = 0;
  int max_a = 0;
  for (int a = m; a > 1; a--) {
    auto [kill, diff] = fun(a);
    if (kill > max_kill) {
      max_kill = kill;
      max_diff = diff;
      max_a = a;
    }
  }
  double kill1 = 0.5 / m + 0.5;
  if (kill1 > max_kill) {
    max_kill = kill1;
    max_diff = 180;
    max_a = 1;
  }
  cout << max_diff << "\n" << max_a << endl;
  return 0;
}

/*

10 5
30
35
45
90
130
259
260
289
300
352

*/