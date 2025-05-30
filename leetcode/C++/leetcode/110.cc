#include <bits/stdc++.h>
#include <functional>
#include <set>
#include <unordered_map>

using namespace std;

// Definition for a binary tree node.
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  explicit TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right)
      : val(x), left(left), right(right) {}
};

class Solution {
public:
  static bool isBalanced(TreeNode *root) {
    unordered_map<TreeNode *, int> dp;
    function<int(TreeNode *)> get_depth = [&](TreeNode *root) -> int {
      if (root == nullptr) {
        return 0;
      }
      auto it = dp.find(root);
      if (it == dp.end()) {
        int lef = get_depth(root->left);
        int rig = get_depth(root->right);
        if (lef == -1 || rig == -1) {
          dp[root] = -1;
        } else {
          int dif = abs(lef - rig);
          if (dif > 1) {
            dp[root] = -1;
          } else {
            dp[root] = max(lef, rig) + 1;
          }
        }
      }
      return dp[root];
    };
    return get_depth(root) != -1;
  }
};
int main() {
  // auto *n8 = new TreeNode(8);
  // auto *n4 = new TreeNode(4,n8,nullptr);
  // auto *n5 = new TreeNode(5);
  // auto *n2 = new TreeNode(2,n4,n5);
  // auto *n6 = new TreeNode(6);
  // auto *n3 = new TreeNode(3,n6,nullptr);
  // auto *n1 = new TreeNode(1,n2,n3);

  auto *n4 = new TreeNode(4);
  auto *n44 = new TreeNode(4);
  auto *n3 = new TreeNode(3, n4, nullptr);
  auto *n33 = new TreeNode(2, nullptr, n44);
  auto *n2 = new TreeNode(2, n3, nullptr);
  auto *n22 = new TreeNode(2, nullptr, n33);
  auto *n1 = new TreeNode(1, n2, n22);
  auto x = Solution::isBalanced(n1);
  cout << x;
  return 0;
}
