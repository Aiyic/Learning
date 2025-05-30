// #include "../base/Node.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  static vector<vector<string>> partition(string s) {
    vector<vector<string>> results;
    int n = s.length();
    auto judge = [](string s) {
      int i = 0;
      int j = s.length() - 1;
      while (i < j) {
        if (s[i++] != s[j--]) {
          return false;
        }
      }
      return true;
    };

    vector<string> res = {string(1, s[0])};
    function<void(int)> back = [&](int idx) {
      if (idx >= n) {
        if (judge(res.back())) {
          results.push_back(res);
        }
        return;
      }
      if (judge(res.back())) {
        res.emplace_back(1, s[idx]);
        back(idx + 1);
        res.pop_back();
      }
      res.back() += s[idx];
      back(idx + 1);
      res.back().erase(res.back().length() - 1);
    };
    back(1);
    return results;
  }
};

int main() {
  auto x = Solution::partition("a");
  cout << 1;
  return 0;
}
