#include <bits/stdc++.h>
using namespace std;

int main() {
  int t;
  cin >> t;
  while ((t--) != 0) {
    int n;
    cin >> n;
    set<int> lower;
    unordered_set<int> normal;
    set<int> upper;
    vector<int> ops(n);
    for (int i = 0; i < n; ++i) {
      int op;
      int x;
      cin >> op >> x;
      x--;
      ops[x] = op;
      if (op == -1) {
        lower.insert(x);
      } else if (op == 1) {
        upper.insert(x);
      } else {
        normal.insert(x);
      }
    }
    deque<int> music;
    vector<int> sort_music(n);
    for (int i : lower) {
      music.push_back(i);
    }
    for (int i : upper) {
      music.push_back(i);
    }
    for (int i = 0; i < n; ++i) {
      auto it = normal.find(i);
      if (it != normal.end()) {
        sort_music[i] = i;
      } else {
        sort_music[i] = music.front();
        music.pop_front();
      }
    }
    bool flag = true;
    for (int i = 0; i < n; ++i) {
      int idx = sort_music[i];
      int op = ops[idx];
      if (op == -1 && i < idx) {
      } else if (op == 1 && i > idx) {
      } else if (op == 0 && i == idx) {
      } else {
        flag = false;
        break;
      }
    }
    if (flag) {
      cout << "YES" << endl;
    } else {
      cout << "NO" << endl;
    }
  }

  return 0;
}

/*

2
2
1 1
-1 2
5
0 2
-1 3
-1 4
0 1
-1 5

*/