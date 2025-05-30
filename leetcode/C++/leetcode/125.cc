// #include "../base/Node.h"
#include <bits/stdc++.h>
#include <string>

using namespace std;

class Solution {
public:
  static bool isPalindrome(const string &s) {
    string lower_s;
    int dif = 'a' - 'A';
    for (char c : s) {
      if (c >= 'A' && c <= 'Z') {
        c += dif;
        lower_s += c;
      } else if ((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')) {
        lower_s += c;
      }
    }
    int l = 0;
    int r = lower_s.length() - 1;
    while (l < r) {
      if (lower_s[l++] != lower_s[r--]) {
        return false;
      }
    }
    return true;
  }
};

int main() {
  vector<int> arr = {1, 2, 3, 4, 4};
  string s = "hello world";
  auto a = Solution::isPalindrome(s);
  cout << 1;
  return 0;
}
