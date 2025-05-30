#include <algorithm>
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
  static TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
    if (preorder.empty()) {
      return nullptr;
    }
    if (preorder.size() == 1) {
      return new TreeNode(preorder[0]);
    }
    auto x = ranges::find(inorder, preorder[0]);
    auto *root = new TreeNode(*x);
    vector<int> inoreder_left(inorder.begin(), x);
    vector<int> inoreder_right(next(x, 1), inorder.end());
    vector<int> preorder_left(next(preorder.begin()),
                              next(preorder.begin(), 1 + inoreder_left.size()));
    vector<int> preorder_right(next(preorder.begin(), 1 + inoreder_left.size()),
                               preorder.end());
    root->left = buildTree(preorder_left, inoreder_left);
    root->right = buildTree(preorder_right, inoreder_right);
    return root;
  }
};

int main() {
  vector<int> preorder = {1,2};
  vector<int> inorder = {2,1};
  auto *x = Solution::buildTree(preorder, inorder);
  cout << 1;
  return 0;
}
