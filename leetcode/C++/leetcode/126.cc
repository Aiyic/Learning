// #include "../base/Node.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  static vector<vector<string>> findLadders(string beginWord, string endWord,
                                            vector<string> &wordList) {
    vector<vector<string>> res;
    int n = wordList.size();
    vector<unordered_set<int>> edge(n + 1);
    auto is_sim = [](string x, string y) {
      int count = 0;
      for (int i = 0; i < x.size(); ++i) {
        if (x[i] != y[i]) {
          count++;
        }
      }
      return count == 1;
    };
    int start = -1;
    int end = -1;
    for (int i = 0; i < n; ++i) {
      if (wordList[i] == beginWord) {
        start = i;
      }
    }
    if (start == -1) {
      wordList.insert(wordList.begin(), beginWord);
      start = 0;
      n++;
    }
    for (int i = 0; i < n; ++i) {
      if (wordList[i] == endWord) {
        end = i;
      }
      for (int j = i + 1; j < n; ++j) {
        if (is_sim(wordList[i], wordList[j])) {
          edge[i].insert(j);
          edge[j].insert(i);
        }
      }
    }
    if (end == -1) {
      return res;
    }
    vector<int> visit(n, INT_MAX);
    vector<unordered_set<int>> last(n);
    unordered_set<int> now;
    unordered_set<int> next;
    int level = 1;
    now.insert(start);
    while (!now.empty()) {
      for (int u : now) {
        for (int v : edge[u]) {
          if (visit[v] < level) {
            continue;
          }
          visit[v] = level;
          last[v].insert(u);
          next.insert(v);
        }
      }
      now.clear();
      now.swap(next);
      level++;
    }
    vector<int> path;
    function<void(int)> dfs = [&](int i) {
      path.push_back(i);
      if (i == start) {
        res.emplace_back();
        for (int j : ranges::reverse_view(path)) {
          res.back().push_back(wordList[j]);
        }
      } else {
        for (int prev : last[i]) {
          dfs(prev);
        }
      }
      path.pop_back();
    };
    dfs(end);
    return res;
  }
};

int main() {
  string begin_word = "hit";
  string end_word = "cog";
  vector<string> word_list = {"hot","dot","dog","lot","log"};
  auto a = Solution::findLadders(begin_word, end_word, word_list);
  cout << 1;
  return 0;
}
