#include <bits/stdc++.h>
#include <functional>
#include <stack>
#include <unordered_map>
#include <utility>

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
#ifdef MY_SOLUTION
  unordered_map<int, int> subtree_min_val, subtree_max_val;
  bool isValidBST(TreeNode *root) {
    function<int(TreeNode *)> find_min = [&](TreeNode *root) -> int {
      if (subtree_min_val.find(root->val) != subtree_min_val.end()) {
        return subtree_min_val[root->val];
      }
      if (root->left != nullptr) {
        subtree_min_val[root->val] = find_min(root->left);
      } else {
        subtree_min_val[root->val] = root->val;
      }
      return subtree_min_val[root->val];
    };
    function<int(TreeNode *)> find_max = [&](TreeNode *root) -> int {
      if (subtree_max_val.find(root->val) != subtree_max_val.end()) {
        return subtree_max_val[root->val];
      }
      if (root->right != nullptr) {
        subtree_max_val[root->val] = find_max(root->right);
      } else {
        subtree_max_val[root->val] = root->val;
      }
      return subtree_max_val[root->val];
    };

    if (root == nullptr) {
      return true;
    }
    if (((root->left == nullptr) || find_max(root->left) < root->val) &&
        ((root->right == nullptr) || find_min(root->right) > root->val)) {
      return isValidBST(root->left) && isValidBST(root->right);
    }
    return false;
  }

#else

  // DFS
  static bool isValidBST(TreeNode *root) {
    stack<TreeNode *> visit;
    TreeNode *now = root;
    while (now != nullptr) {
      visit.push(now);
      now = now->left;
    }
    int last = visit.top()->val;
    bool flag = false;
    while (!visit.empty()) {
      now = visit.top();
      visit.pop();
      if (flag && now->val <= last) {
        return false;
      }
      flag = true;
      last = now->val;
      if (now->right != nullptr) {
        visit.push(now->right);
        now = visit.top()->left;
        while (now != nullptr) {
          visit.push(now);
          now = now->left;
        }
      }
    }
    return true;
  }
#endif
};

int main() {
  auto *node1 = new TreeNode(0);
  auto *node2 = new TreeNode(3);
  auto *node3 = new TreeNode(4);
  auto *node4 = new TreeNode(6);
  auto *node5 = new TreeNode(2, nullptr, node2);
  auto *node6 = new TreeNode(1, node1, node5);
  auto *node7 = new TreeNode(5, node3, node4);
  auto *node8 = new TreeNode(3, node6, node7);

  auto *node9 = new TreeNode(2147483647);

  auto a = Solution().isValidBST(node7);
  cout << 1;
  return 0;
}
