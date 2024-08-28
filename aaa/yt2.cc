#include <bits/stdc++.h>
#include <type_traits>
#include <vector>

using namespace std;

struct P {
  int x, y;
};
bool isInter(P a, P b, P c, P d) {
  int d1 = (c.y - a.y) * (b.x - a.x) - (b.y - a.y) * (c.x - a.x);
  int d2 = (d.y - a.y) * (b.x - a.x) - (b.y - a.y) * (d.x - a.x);
  int d3 = (a.y - c.y) * (d.x - c.x) - (d.y - c.y) * (a.x - c.x);
  int d4 = (b.y - c.y) * (d.x - c.x) - (d.y - c.y) * (b.x - c.x);
  return d1 * d2 < 0 && d3 * d4 < 0;
}
int main() {
  int n;
  int m;
  cin >> n >> m;

  vector<P> point(n);
  vector<pair<P, P>> wall(m);

  for (int i = 0; i < n; ++i) {
    cin >> point[i].x >> point[i].y;
  }
  for (int i = 0; i < m; ++i) {
    cin >> wall[i].first.x >> wall[i].first.y >> wall[i].second.x >>
        wall[i].second.y;
  }
  int max_path=0;
  for (int i = 0; i < n; ++i) {
    for (int j = i+1; j < n; ++j) {
        bool vaild=true;
        for(int k=0; k<m ;++k){
            if(isInter(point[i], point[j], wall[k].first, wall[k].second)){
                vaild=false;
                break;
            }
        }
        if(vaild){
            max_path++;
        }
    }
  }
  cout << max_path << endl;
  return 0;
}

/*

3 1
1 1
3 1
3 3
2 0 2 3


  0 1 2 3
0
1   *
2 -------
3   *   *


*/