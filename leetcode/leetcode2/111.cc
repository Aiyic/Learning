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
  static int minDepth(TreeNode *root) {
    if (root == nullptr) {
      return 0;
    }
    deque<TreeNode *> visit;
    deque<TreeNode *> next_visit;
    visit.push_back(root);
    int depth = 1;
    while (!visit.empty()) {
      auto *node = visit.front();
      if(node->left == nullptr && node->right == nullptr){
        return depth;
      }
      if (node->left != nullptr) {
        next_visit.push_back(node->left);
      }
      if (node->right != nullptr) {
        next_visit.push_back(node->right);
      }
      visit.pop_front();
      if (visit.empty() && !next_visit.empty()) {
        visit.swap(next_visit);
        depth++;
      }
    }
    return depth;
  }
};

int main() {
  auto *n1 = new TreeNode(9);
  auto *n2 = new TreeNode(15);
  auto *n3 = new TreeNode(7);
  auto *n4 = new TreeNode(20, n2, n3);
  auto *n5 = new TreeNode(3, n1, n4);
  auto x = Solution::minDepth(n5);
  cout << 1;
  return 0;
}
