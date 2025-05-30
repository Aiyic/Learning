
#include <bits/stdc++.h>
#include <vector>
using namespace std;

class Solution {
public:
  static vector<vector<int>> generate(int numRows) {
    if (numRows == 1) {
      vector<vector<int>> res;
      res.push_back({1});
      return res;
    }
    auto res = generate(numRows - 1);
    auto &back = res.back();
    vector<int> newline;
    int last = 0;
    for (auto i : back) {
      newline.push_back(last+i);
      last = i;
    }
    newline.push_back(1);
    res.emplace_back(std::move(newline));
    return res;
  }
};
int main() {

  auto a = Solution::generate(3);
  cout << 1;
  return 0;
}
