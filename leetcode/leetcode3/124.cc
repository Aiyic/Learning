#include "../Node.h"
#include <array>
#include <bits/stdc++.h>
#include <functional>
#include <iterator>
#include <stack>

using namespace std;

class Solution {
public:
  static int maxPathSum(TreeNode *root) {
    unordered_map<TreeNode *, array<int, 2>> dp;
    dp[nullptr] = {-1001, -1001};
    // dp[node*][0/1] 不选/选当前节点的v的子树最大路径和
    function<array<int, 2>(TreeNode *)> dfs =
        [&](TreeNode *node) -> array<int, 2> {
      if (dp.find(node) == dp.end()) {
        auto [l1, l2] = dfs(node->left);
        auto [r1, r2] = dfs(node->right);
        int v = node->val;
        int now1 = max({l1, r1, l2, r2, l2 + v, r2 + v, l2 + r2 + v});
        int now2 = max({v, l2 + v, r2 + v});
        dp[node] = {now1, now2};
      }
      return dp[node];
    };
    auto [now1, now2] = dfs(root);
    return max(now1, now2);
  }
};

int main() {
  TreeNode *root = stringToTree("[-3]");
  auto a = Solution::maxPathSum(root);
  cout << 1;
  return 0;
}
