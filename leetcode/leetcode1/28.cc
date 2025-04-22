// #include "../base/Node.h"
#include <bits/stdc++.h> 

using namespace std;

class Solution {
public:
  static int strStr(const string &haystack, const string &needle) {
    vector<int> next(needle.length());

    auto getNext = [&](const string &s) {
      int n = s.length();
      next.resize(n); // 确保 next 数组的大小
      next[0] = 0;    // 第一个字符的 next 值为 0
      for (int i = 1, j = 0; i < n;) {
        if (s[i] == s[j]) {
          j++;
          next[i] = j;
          i++;
        } else {
          if (j > 0) {
            j = next[j - 1]; // 根据 next 数组调整 j
          } else {
            next[i] = 0; // 当 j == 0 时，next[i] 设为 0
            i++;
          }
        }
      }
    };

    getNext(needle);

    for (int i = 0; i < haystack.length(); i++) {
      for (int j = 0; j < needle.length(); ) {
        if (haystack[i + j] == needle[j]) { // 匹配
          j++;
          if (j == needle.length()) {
            return i;
          }
        } else { // 不匹配
          if (next[j] != 0) {
            i += next[j];            
          } 
          break;
        }
      }
    }
    return -1;
  }
};

int main() {
  string s = "leetcode";
  string s1 = "leeto";
  auto a = Solution::strStr(s, s1);
  cout << a;
  return 0;
}

/*

~

*/
