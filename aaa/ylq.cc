
#include <bits/stdc++.h>
using namespace std;
struct Point {
  int x;
  int y;
  Point(int xx, int yy) : x(xx), y(yy) {}
};

// 自定义比较函数
struct PointComparator {
  bool operator()(const Point &a, const Point &b) const {
    if (a.x != b.x) {
      return a.x < b.x;
    }
    return a.y < b.y;
  }
};
class Solution {
public:
  static int Findpath(int map_width, int map_height, vector<vector<int>> &grids,
                      Point start_pos, Point end_pos) {

    map<Point, int, PointComparator> now;
    map<Point, int, PointComparator> next;
    map<Point, int, PointComparator> visit;
    vector<pair<int, int>> nerber = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    now.insert({start_pos, 0});

    while (!now.empty()) {
      for (auto &[p, i] : now) {
        if (visit.find(p) != visit.end() && i >= visit[p]) {
        } else {
          visit[p] = i;
          for (auto [x, y] : nerber) {
            int xx = p.x + x;
            int yy = p.y + y;
            if (xx >= 0 && xx < map_width && yy >= 0 && yy < map_height &&
                grids[xx][yy] != 0) {
              next.insert({{xx, yy}, i + grids[xx][yy]});
            }
          }
        }
      }
      now.clear();
      now.swap(next);
    }
    return visit[end_pos];
  }
};

int main() {
  vector<vector<int>> grids = {{1, 3, 2, 2, 3, 0}, 
                               {3, 0, 1, 1, 3, 2},
                               {1, 3, 2, 0, 1, 3},
                               {2, 1, 3, 3, 2, 1},
                               {1, 0, 3, 2, 2, 1},
                               {3, 2, 1, 0, 3, 2}};
  auto a = Solution::Findpath(6, 6, grids, {0, 0}, {2, 2});
  cout << 1;
  return 0;
}

/*


*/