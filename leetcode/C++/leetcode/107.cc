
#include <algorithm>
#include <bits/stdc++.h>
#include <deque>
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
  static vector<vector<int>> levelOrderBottom(TreeNode *root) {
    vector<vector<int>> res;
    if(root == nullptr){
        return res;
    }
    vector<int> now;
    deque<TreeNode *> visit;
    deque<TreeNode *> visit_next;
    visit.push_back(root);
    while (!visit.empty()) {
      auto *x = visit.front();
      visit.pop_front();
      if (x->left != nullptr) {
        visit_next.push_back(x->left);
      }
      if (x->right != nullptr) {
        visit_next.push_back(x->right);
      }
      now.push_back(x->val);
      if (visit.empty()) {
        res.push_back(now);
        now.clear();
        visit.swap(visit_next);
      }
    }
    reverse(res.begin(),res.end());
    return res;
  }
};

int main() {
  auto *n1 = new TreeNode(9);
  auto *n2 = new TreeNode(15);
  auto *n3 = new TreeNode(7);
  auto *n4 = new TreeNode(20, n2, n3);
  auto *n5 = new TreeNode(3, n1, n4);
  auto x = Solution::levelOrderBottom(n5);
  cout << 1;
  return 0;
}
