// #include "../base/Node.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  static int ladderLength(string beginWord, string endWord,
                          vector<string> &wordList) {
    int n = wordList.size();
    unordered_set<string> word_set(wordList.begin(), wordList.end());
    word_set.insert(beginWord);
    if (!word_set.contains(endWord)) {
      return 0;
    }
    unordered_set<string> visit;
    unordered_set<string> now;
    unordered_set<string> next;
    int level = 1;
    now.insert(beginWord);
    while (!now.empty()) {
      for (const auto &u : now) {
        for (int j = 0; j < u.size(); ++j) {
          for (char c = 'a'; c <= 'z'; ++c) {
            if (u[j] == c) {
              continue;
            }
            string ss(u);
            ss[j] = c;
            if (word_set.contains(ss)) {
              if (visit.contains(ss)) {
                continue;
              }
              visit.insert(ss);
              if (ss == endWord) {
                return level + 1;
              }
              next.insert(ss);
            }
          }
        }
      }
      now.clear();
      now.swap(next);
      level++;
    }
    return 0;
  }
};

int main() {
  string begin_word = "hit";
  string end_word = "cog";
  vector<string> word_list = {"hot", "dot", "dog", "lot", "log", "cog"};
  auto a = Solution::ladderLength(begin_word, end_word, word_list);
  cout << 1;
  return 0;
}
