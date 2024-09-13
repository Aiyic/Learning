#include <bits/stdc++.h>
#include <functional>
#include <vector>

using namespace std;

// Definition for singly-linked list.
struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  explicit ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};
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
  static TreeNode *sortedListToBST(ListNode *head) {
    vector<int> list;
    while (head) {
      list.push_back(head->val);
      head = head->next;
    }
    function<TreeNode *(int, int)> fun = 
        [&](int left,int right) -> TreeNode * {
      int n = list.size();
      if (left >= right) {
        return nullptr;
      }
      int half = left + (right - left) / 2;
      auto *node = new TreeNode(list[half]);
      node->left = fun(left, half);
      node->right = fun(half + 1, right);
      return node;
    };
    return fun(0, list.size());
  }
};

int main() {
  auto *x = Solution::sortedListToBST(nullptr);
  cout << 1;
  return 0;
}
