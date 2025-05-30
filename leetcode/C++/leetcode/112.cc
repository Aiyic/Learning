#include <bits/stdc++.h>
#include <cstddef>
#include <functional>
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
  static bool hasPathSum(TreeNode *root, int targetSum) {
    if (root == nullptr) {
      return false;
    }
    function<bool(TreeNode *, TreeNode *, int)> fun =
        [&fun](TreeNode *parent, TreeNode *node, int targetSum) -> bool {
      if (node == nullptr) {
        return targetSum == 0 &&
               ((parent->left == nullptr) && (parent->right == nullptr));
      }
      return fun(node, node->left, targetSum - node->val) ||
             fun(node, node->right, targetSum - node->val);
    };
    return fun(nullptr, root, targetSum);
  }
};

int main() {
  auto *n1 = new TreeNode(7);
  auto *n2 = new TreeNode(2);
  auto *n3 = new TreeNode(11, n1, n2);
  auto *n4 = new TreeNode(4, n3, nullptr);
  auto *n5 = new TreeNode(5, n4, nullptr);
  auto x = Solution::hasPathSum(n5, 22);
  cout << x;
  return 0;
}
