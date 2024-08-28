#include <functional>
#include <iostream>
#include <limits>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;

class Solution {
public:
  /* Write Code Here */
  int numberOfPatrolBlocks(vector<vector<int>> block) {
    int i = 0;
    int j = 0;
    int wdsa = 1;
    int count = 1;
    block[0][0] = 2;
    int trans = 0;
    vector<pair<int, int>> path;
    path.emplace_back(0,0);
    auto can_go = [&block](int i, int j) {
      if (i >= 0 && i < block.size() && j >= 0 && j < block[0].size()) {
        if (block[i][j] == 0 ) {
          block[i][j] = 2;
          return true;
        } 
      }
      return false;
    };
    function<bool()> next_idx = [&]() -> bool {
      if (wdsa == 0 && can_go(i - 1, j)) {
        i--;
      } else if (wdsa == 1 && can_go(i, j + 1)) {
        j++;
      } else if (wdsa == 2 && can_go(i + 1, j)) {
        i++;
      } else if (wdsa == 3 && can_go(i, j - 1)) {
        j--;
      } else {
        trans++;
        if (trans > 4) {
        block[i][j] = 1;
        path.pop_back();
          return false;
        }
        wdsa = (wdsa + 1) % 4;
        return next_idx();
      }
      if(path.back().first == i && path.back().second == j){

      }
      else{
        path.emplace_back(i, j);
      }

      trans = 0;
      return true;
    };

    while (next_idx()) {
      count++;
    }
    return count;
  }
};
int main() {
  int res;

  int block_rows = 0;
  int block_cols = 0;
  cin >> block_rows >> block_cols;
  vector<vector<int>> block(block_rows);
  for (int block_i = 0; block_i < block_rows; block_i++) {
    for (int block_j = 0; block_j < block_cols; block_j++) {
      int block_tmp;
      cin >> block_tmp;
      block[block_i].push_back(block_tmp);
    }
  }
  Solution *s = new Solution();
  res = s->numberOfPatrolBlocks(block);
  cout << res << endl;

  return 0;
}

/*

3 3
0 0 0
1 0 1
1 1 1

7


*/