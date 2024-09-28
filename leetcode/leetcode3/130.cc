// #include "../base/Node.h"
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  static void solve(vector<vector<char>> &board) {
    int m = board.size();
    int n = board[0].size();

    auto pair2int = [&](pair<int, int> p) { return p.first * n + p.second; };
    auto int2prir = [&](int i) -> pair<int, int> { return {i / n, i % n}; };
    unordered_set<int> point;
    unordered_set<int> arround;

    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (board[i][j] == 'O') {
          point.insert(pair2int({i, j}));
          if(i==0 || i==m-1 || j==0 || j==n-1){
            arround.insert(pair2int({i, j}));
          }
        }
      }
    }

    unordered_set<int> visit;
    while (!arround.empty()) {
      auto now = *arround.begin();
      if(visit.find(now)!=visit.end()){
        continue;
      }
      visit.insert(now);
      auto [i, j] = int2prir(now);
      point.erase(now);
      arround.erase(now);
      vector<pair<int, int>> nerber = {
          {i - 1, j},
          {i + 1, j},
          {i, j - 1},
          {i, j + 1},
      };
      for (auto [x, y] : nerber) {
        int next = pair2int({x,y});
        if(point.find(next)!=point.end()){
            arround.insert(next);
        }
      }
    }

    for(auto p:point){
        auto [i,j] = int2prir(p);
        board[i][j] = 'X';
    }
  }
};

int main() {
  vector<vector<char>> board = {{'X', 'X', 'X', 'X'},
                                {'X', 'O', 'O', 'X'},
                                {'X', 'X', 'O', 'X'},
                                {'X', 'O', 'X', 'X'}};
  Solution::solve(board);
  cout << 1;
  return 0;
}
