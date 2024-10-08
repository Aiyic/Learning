
#include <bits/stdc++.h>
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
  vector<int> inorderTraversal(TreeNode *root) {
    if (root != nullptr) {
      vector<int> res;
      for (auto &x : inorderTraversal(root->left)) {
        res.push_back(x);
      }
      res.push_back(root->val);
      for (auto &x : inorderTraversal(root->right)) {
        res.push_back(x);
      }
      return res;
    }
    return {};
  }
};

int main() {
  Solution s;
  TreeNode *root;
  auto x = s.inorderTraversal(root);
  cout << 1;
  return 0;
}

/*

0 + list[]
1 + reverse[]

*/
