// #include "../base/Node.h"
#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
  static int candy(vector<int> &ratings) {
    int n = ratings.size();

    auto fun = [&](vector<int> &ratings) -> pair<int, int> {
      int count = 1;
      int tmp = 1;
      int min_idx = 0;
      for (int i = 1; i < n; ++i) {
        if (ratings[i] > ratings[i - 1]) {
          tmp++;
        } else {
          if (tmp > count) {
            count = tmp;
            min_idx = i - count;
          }
          tmp = 1;
        }
      }

      if (tmp > count) {
        count = tmp;
        min_idx = n - count;
      }
      return {min_idx, count};
    };

    auto [idx, count] = fun(ratings);
    ranges::reverse(ratings);
    auto [idx2, count2] = fun(ratings);
    if (count < count2) {
      idx = n - 1 - idx2;
    }
    ranges::reverse(ratings);

    vector<int> candys(n);
    candys[idx] = 1;
    for (int i = idx + 1; i < n; ++i) {
      if (ratings[i] > ratings[i - 1]) {
        candys[i] = candys[i - 1] + 1;
      } else {
        candys[i] = 1;
      }
    }
    for (int i = idx - 1; i >= 0; --i) {
      if (ratings[i] > ratings[i + 1]) {
        candys[i] = candys[i + 1] + 1;
      } else {
        candys[i] = 1;
      }
    }

    return accumulate(candys.begin(), candys.end(), 0);
  }
};

int main() {
  vector<int> ratings = {1, 3,2,2,1};

  auto a = Solution::candy(ratings);
  cout << 1;
  return 0;
}

/*

1 1 2 1
x 1 2 1

*/
