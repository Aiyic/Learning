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
  static TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder) {
    if (postorder.empty()) {
      return nullptr;
    }
    if (postorder.size() == 1) {
      return new TreeNode(postorder.back());
    }
    auto x = ranges::find(inorder, postorder.back());
    auto *root = new TreeNode(*x);
    vector<int> inoreder_left(inorder.begin(), x);
    vector<int> inoreder_right(next(x, 1), inorder.end());
    vector<int> postorder_left(postorder.begin(),
                               next(postorder.begin(), inoreder_left.size()));
    vector<int> postorder_right(next(postorder.begin(), inoreder_left.size()),
                                prev(postorder.end()));
    root->left = buildTree(inoreder_left, postorder_left);
    root->right = buildTree(inoreder_right, postorder_right);
    return root;
  }
};

int main() {
  vector<int> inorder = {2, 1};
  vector<int> postorder = {1, 2};
  auto *x = Solution::buildTree(inorder, postorder);
  cout << 1;
  return 0;
}
