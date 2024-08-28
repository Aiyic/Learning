#include <bits/stdc++.h>
#include <vector>

using namespace std;

struct P {
  int x, y, z;
};

int main() {
  int n;
  cin >> n;
  while ((n--) != 0) {
    int m;
    cin >> m;
    vector<P> block(m);
    for (int i = 0; i < m; ++i) {
      cin >> block[i].x >> block[i].y >> block[i].z;
    }
    set<int> s;
    for (auto &p : block) {
      s.insert((p.z * 101 + p.y) * 101 + p.x);
    }

    set<int> s_ok;
    for (auto pp = s.begin(); pp != s.end(); ) {
      auto p = *pp;
      int x = p % 101;
      int y = p / 101 % 101;
      int z = p / 101 / 101;
      if (z == 1) {
        s.erase(p);
        s_ok.insert(p);
        pp = s.begin();
        continue;
      } else {
        vector<int> arrange = {p + 101 * 101, p - 101 * 101, p + 101,
                               p - 101,       p + 1,         p - 1};
        bool find_one = false;
        bool find_all = true;
        for (auto node : arrange) {
          auto it = s.find(node);
          if (it != s.end()) {
            find_one = true;
          } else {
            find_all = false;
          }
        }
        if (find_one && !find_all) {
          s.erase(p);
          s_ok.insert(p);
          pp = s.begin();
        continue;
        } 
      }
      ++pp;
    }
    if (s.empty()) {
      cout << "Yes" << endl;
    } else {
      cout << "No" << endl;
    }
  }
  return 0;
}

/*

2
3
1 1 1
1 2 1
1 3 1
3
1 1 1
1 2 1
1 3 2


*/