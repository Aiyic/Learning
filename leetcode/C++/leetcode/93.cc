
#include <bits/stdc++.h>
#include <functional>
#include <vector>

using namespace std;

class Solution {
public:
  static vector<string> restoreIpAddresses(const string& s) {
    for (char c : s) {
      if (c >= '0' && c <= '9') {
        ;
      } else {
        return {};
      }
    };
    auto get_one_num = [](const string &s) -> bool {
      if (s.length() > 3 || s.length() <= 0) {
        return false;
      }
      if (s.length() > 1 && s[0] == '0') {
        return false;
      }
      int x = atoi(s.c_str());
      return x >= 0 && x <= 255;
    };

    vector<string> back;
    vector<string> results;
    function<bool(string, int)> check_str = [&](const string &s,
                                                int n) -> bool {
      bool res = true;
      if (n == 0) {
        if (s == "") {
          results.emplace_back(back[0] + "." + back[1] + "." + back[2] + "." +
                               back[3]);
          return true;
        }
        return false;
      }
      for (int i = 1; i <= 3; ++i) {
        if (s.length() < i) {continue;}
        string pos = string(s, 0, i);
        if (get_one_num(pos)) {
          back.push_back(pos);
          res &= check_str(string(s, i), n - 1);
          back.pop_back();
        }
      }
      return res;
    };

    check_str(s, 4);
    return results;
  }
};

int main() {
  Solution s;

  auto x = s.restoreIpAddresses("101023");
  cout << 1;
  return 0;
}

/*

0 + list[]
1 + reverse[]

*/
