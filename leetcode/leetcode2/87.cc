
#include <array>
#include <bits/stdc++.h>
#include <bitset>
#include <cassert>
#include <cstdint>
#include <functional>
#include <utility>
#include <vector>

using namespace std;

class Solution {
public:
  map<array<int8_t, 3>, int8_t> res_set;
  bool isScramble(string s1, string s2, int pos1 = 0, int pos2 = 0) {
    assert(s1.length() == s2.length());
    if (s1.length() <= 1 || s1 == s2) {
      return s1 == s2;
    }
    array<int8_t, 3> arr;
    arr[0] = pos1;
    arr[1] = pos2;
    arr[2] = s1.length();
    if (res_set[arr] != 0) {
      return res_set[arr] == 1;
    }
    map<char, int> tab;
    map<char, int> tab_reverse;
    bitset<26> is_same;
    bitset<26> is_same_reverse;
    bool res = false;
    for (int i = 0; i < s1.length() - 1; ++i) {
      tab[s1[i]]++;
      if (tab[s1[i]] != 0) {
        is_same.set(s1[i] - 'a');
      } else {
        is_same.reset(s1[i] - 'a');
      }

      tab_reverse[s1[i]]++;
      if (tab_reverse[s1[i]] != 0) {
        is_same_reverse.set(s1[i] - 'a');
      } else {
        is_same_reverse.reset(s1[i] - 'a');
      }

      tab[s2[i]]--;
      if (tab[s2[i]] != 0) {
        is_same.set(s2[i] - 'a');
      } else {
        is_same.reset(s2[i] - 'a');
      }

      int idx = s2.length() - i - 1;
      tab_reverse[s2[idx]]--;
      if (tab_reverse[s2[idx]] != 0) {
        is_same_reverse.set(s2[idx] - 'a');
      } else {
        is_same_reverse.reset(s2[idx] - 'a');
      }

      if (!is_same.any()) {
        res |= (isScramble(string(s1, 0, i + 1), string(s2, 0, i + 1)) &&
                isScramble(string(s1, i + 1), string(s2, i + 1), i + 1, i + 1));
      }
      if (res) {
        break;
      }
      if (!is_same_reverse.any()) {
        res |= (isScramble(string(s1, 0, i + 1), string(s2, idx), 0, idx) &&
                isScramble(string(s1, i + 1), string(s2, 0, idx), i + 1, 0));
      }
      if (res) {
        break;
      }
    }
    if (res) {
      res_set[arr] = 1;
    } else {
      res_set[arr] = -1;
    }
    return res;
  }
};

int main() {
  Solution s;

  auto a = s.isScramble("ccababcaabcb", "bccbccaaabab");
  cout << 1;
  return 0;
}
