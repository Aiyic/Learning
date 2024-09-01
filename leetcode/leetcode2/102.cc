#include <bits/stdc++.h>
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
    static vector<vector<int>> levelOrder(TreeNode* root) {
      vector<vector<int>> results;
      if(root == nullptr) return results;
      queue<pair<TreeNode*, int>> nodes;
      nodes.emplace(root,0);
      int level = 0;
      vector<int> res;
      while(!nodes.empty()){
        auto x = nodes.front();
        nodes.pop();
        if(x.second != level){
          results.push_back(res);
          res.clear();
          level++;
        }
        res.push_back(x.first->val);
        if(x.first->left) nodes.emplace(x.first->left,level+1);
        if(x.first->right) nodes.emplace(x.first->right,level+1);
      }
      results.push_back(res);
      return results;
    }
};

int main() {
  auto* n1 = new TreeNode(9);
  auto* n2 = new TreeNode(15);
  auto* n3 = new TreeNode(7);
  auto* n4 = new TreeNode(20, n2,n3);
  auto* n5 = new TreeNode(3, n1,n4);
  auto x = Solution::levelOrder(n5);
  cout << 1;
  return 0;
}
