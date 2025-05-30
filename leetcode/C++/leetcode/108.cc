

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
  static TreeNode *sortedArrayToBST(vector<int> &nums) {
    int n = nums.size();
    if (n == 0) {
      return nullptr;
    }
    if (n == 1) {
      return new TreeNode(nums[0]);
    }
    int half = n / 2;
    auto *root = new TreeNode(nums[half]);
    vector<int> left(nums.begin(), next(nums.begin(), half));
    vector<int> right(next(nums.begin(), half + 1), nums.end());
    root->left = sortedArrayToBST(left);
    root->right = sortedArrayToBST(right);
    return root;
  }
};

int main() {
  vector<int> num = {-10, -3, 0, 5, 9};
  auto *x = Solution::sortedArrayToBST(num);
  cout << 1;
  return 0;
}
