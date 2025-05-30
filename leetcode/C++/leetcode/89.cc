
#include <bits/stdc++.h>
#include <ranges>

using namespace std;

class Solution {
public:
  vector<int> grayCode(int n) {
    if (n == 1) {
      return vector<int>{0, 1};
    }
    auto last = grayCode(n - 1);
    vector<int> res(last);
    for (int &it : ranges::reverse_view(last)) {
      res.push_back(it + (1 << (n-1)));
    }
    return res;
  }
};

int main() {
  Solution s;

  auto x = s.grayCode(3);
  cout << 1;
  return 0;
}

/*

0 + list[]
1 + reverse[]

*/
