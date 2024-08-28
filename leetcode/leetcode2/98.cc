#include <bits/stdc++.h>
#include <functional>
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
  unordered_map<int, pair<int, int>> rec;
  bool isValidBST(TreeNode *root) {
    function<pair<int, int>(TreeNode* )> cacl = [&](TreeNode* node) -> pair<int, int> {
      int val = node->val;
      auto it = rec.find(val);
      if(it != rec.end()){
        return rec[val];
      }
      auto lef = cacl(node->left);
      auto rig = cacl(node->right);
      rec[val] = {lef.second,rig.first};
      return rec[val];
    };
    auto it = cacl(root);
    return it.first<root->val && it.second>root->val; 
  }
};

int main() {
  auto *node1 = new TreeNode();

  auto a = Solution().isValidBST(node1);
  cout << 1;
  return 0;
}
