#include <algorithm>
#include <bits/stdc++.h>
#include <cstddef>
#include <functional>
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
    bool isSymmetric(TreeNode* root) {
      function<bool(TreeNode*, TreeNode*)> symmet = [&](TreeNode* n1, TreeNode* n2) ->bool {
        if((n1 != nullptr) && (n2 != nullptr)){
          return n1->val==n2->val && symmet(n1->left, n2->right) && symmet(n1->right, n2->left);
        }
        return (n1 == nullptr) && (n2 == nullptr);
      };
      return symmet(root->left, root->right);
    }
};

int main() {

  // Solution::isSymmetric();
  cout << 1;
  return 0;
}
