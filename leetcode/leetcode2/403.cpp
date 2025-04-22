#include <bits/stdc++.h>
#include <unordered_map>

using namespace std;

class Solution {
public:
  bool canCross(vector<int> &stones) {
    unordered_map<int, set<int>> dp; // [stone], [k](can jump)
    dp[0].insert(1);
    for (int now = 0; now < stones.size(); now++) {
      int next = now + 1;
      while (next < stones.size()) {
        int diff = stones[next] - stones[now];
        if (dp[now].empty() || diff > *dp[now].rbegin()) {
          next = stones.size();
          break;
        }
        if (dp[now].contains(diff)) {
          dp[next].insert(diff);
          dp[next].insert(diff + 1);
          dp[next].insert(diff - 1);
        } 
        next++;
      }
    }
    return !dp[stones.size() - 1].empty();
  }
};

int main() {
  Solution x;
  vector<int> stones = {0,1,3,6,7};
  auto a = x.canCross(stones);
  return 0;
}
