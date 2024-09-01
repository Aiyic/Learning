#include <algorithm>
#include <bits/stdc++.h>
#include <cstddef>
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
  static bool isSameTree(TreeNode *p, TreeNode *q) {
    if ((p != nullptr) && (q != nullptr)) {
      if (p->val == q->val) {
        return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
      }
    }
    return p == nullptr && q == nullptr;
  }
};

int main() {

  // Solution::isSameTree();
  cout << 1;
  return 0;
}
