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
  static vector<vector<int>> pathSum(TreeNode *root, int targetSum) {
    vector<vector<int>> result;
    vector<int> res;
    function<void(TreeNode *, int)> fun = [&](TreeNode *root, int targetSum) {
      res.push_back(root->val);
      if ((root->left == nullptr) && (root->right == nullptr)) {
        if(root->val == targetSum){
          result.push_back(res);
          res.pop_back();
          return ;
        }
      }
      if (root->left != nullptr) {
        fun(root->left, targetSum-root->val);
      }
      if (root->right != nullptr) {
        fun(root->right, targetSum-root->val);
      }
      res.pop_back();
    };
    if (root == nullptr) {
      return result;
    }
    fun(root, targetSum);
    return result;
  }
};

int main() {
  auto *n1 = new TreeNode(7);
  auto *n2 = new TreeNode(2);
  auto *n3 = new TreeNode(11, n1, n2);
  auto *n4 = new TreeNode(4, n3, nullptr);
  auto *n5 = new TreeNode(5, n4, nullptr);
  auto x = Solution::pathSum(n5, 22);
  cout << 1;
  return 0;
}
