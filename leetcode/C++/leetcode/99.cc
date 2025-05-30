#include <algorithm>
#include <bits/stdc++.h>
#include <utility>
#include <vector>

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
  static void recoverTree(TreeNode *root) {
    vector<TreeNode *> dfs_list;
    function<void(TreeNode *)> dfs = [&](TreeNode *node) {
      if (node->left != nullptr) {
        dfs(node->left);
      }
      dfs_list.push_back(node);
      if (node->right != nullptr) {
        dfs(node->right);
      }
    };

    dfs(root);
    vector<TreeNode *> sort_dfs(dfs_list);
    ranges::sort(sort_dfs, [](const TreeNode *n1, const TreeNode *n2) {
      return n1->val < n2->val;
    });
    vector<TreeNode *> change;
    for (int i = 0; i < dfs_list.size(); ++i) {
      if (dfs_list[i] != sort_dfs[i]) {
        change.push_back(dfs_list[i]);
      }
    }
    swap(change[0]->val, change[1]->val);
  }
};

int main() {
  auto *node1 = new TreeNode(1);
  auto *node2 = new TreeNode(2);
  auto *node3 = new TreeNode(4, node2, nullptr);
  auto *node4 = new TreeNode(3, node1, node3);

  Solution::recoverTree(node4);
  cout << 1;
  return 0;
}
