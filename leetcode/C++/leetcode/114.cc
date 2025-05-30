#include <bits/stdc++.h>
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
  static void flatten(TreeNode *root) {
    function<TreeNode *(TreeNode *)> pre_order =
        [&](TreeNode *root) -> TreeNode * {
      if (root == nullptr) {
        return nullptr;
      }
      if (root->left == nullptr && root->right == nullptr) {
        return root;
      }
      auto *pre_left = pre_order(root->left);
      auto *pre_right = pre_order(root->right);
      if (pre_left != nullptr) {
        auto *tmp = root->right;
        root->right = root->left;
        root->left = nullptr;
        pre_left->right = tmp;
      }
      return pre_right == nullptr ? pre_left : pre_right;
    };
    pre_order(root);
  }
};

int main() {
  auto *n1 = new TreeNode(3);
  auto *n2 = new TreeNode(4);
  auto *n3 = new TreeNode(2, n1, n2);
  auto *n4 = new TreeNode(6);
  auto *n5 = new TreeNode(5, nullptr, n4);
  auto *n6 = new TreeNode(1, n3, n5);
  Solution::flatten(n6);
  cout << 1;
  return 0;
}
