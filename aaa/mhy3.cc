#include <bits/stdc++.h>

using namespace std;

int main() {
  int n;
  int m;
  cin >> n >> m;
  vector<vector<int>> arr(n, vector<int>(m, 0));
  unordered_set<int> node_sea;
  set<set<int>> blocks;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      char c;
      cin >> c;
      if (c == '#') {
        arr[i][j] = 1;
      } else {
        arr[i][j] = 0;
        node_sea.insert(i * 1001 + j);
      }
    }
  }

  while (!node_sea.empty()) {
    set<int> blk;
    auto it = node_sea.begin();
    static function<void(int)> add_node = [&](int local) {
      int yy = local % 1001;
      int xx = local / 1001;
      if (xx < 0 || xx >= n || yy < 0 || yy >= m) {
        return;
      }
      auto it = node_sea.find(local);
      if (it != node_sea.end()) {
        blk.insert(*it);
        node_sea.erase(it);

        add_node(local + 1);
        add_node(local - 1);
        add_node(local + 1001);
        add_node(local - 1001);
      }
    };

    add_node(*it);
    blocks.insert(blk);
    blk.clear();
  }

  int max_land_size = 0;
  for (const auto &blk : blocks) {
    int start;
    for (const auto &local : blk) {
      start = local;
      int yy = local % 1001;
      int xx = local / 1001;
      arr[xx][yy] = 2;
    }

    int land_size = 0;
    unordered_set<int> visit;
    static function<void(int, int)> search_land = [&](int x_, int y_) {
      if (x_ < 0 || x_ >= n || y_ < 0 || y_ >= m) {
        return;
      }
      auto it = visit.find(x_ * 1001 + y_);
      if (arr[x_][y_] > 0 && it == visit.end()) {
        visit.insert(x_ * 1001 + y_);
        land_size++;
        search_land(x_ + 1, y_);
        search_land(x_ - 1, y_);
        search_land(x_, y_ + 1);
        search_land(x_, y_ - 1);
      }
    };
    search_land(start / 1001, start % 1001);
    visit.clear();
    for (const auto &local : blk) {
      int yy = local % 1001;
      int xx = local / 1001;
      arr[xx][yy] = 0;
    }
    max_land_size = max(max_land_size, land_size);
  }
  cout << max_land_size << endl;
  return 0;
}

/*

5 5
##..#
#..#.
###..
.#.#.
#.#..

*/