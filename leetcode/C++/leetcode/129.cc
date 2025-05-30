#include "../base/Node.h"
#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
  static int sumNumbers(TreeNode *root) {
    string s;
    int res = 0;
    function<void(TreeNode *)> back = [&](TreeNode *node) {
      int len = s.size();
      s += to_string(node->val);
      if ((node->left == nullptr) && (node->right == nullptr)) {
        res += stoi(s);
      } else {
        if (node->left != nullptr) {
          back(node->left);
        }
        if (node->right != nullptr) {
          back(node->right);
        }
      }
      s.erase(len);
    };
    back(root);
    return res;
  }
};

int main() {
  auto *root = stringToTree("[4,9,0,5,1]");
  auto a = Solution::sumNumbers(root);
  cout << 1;
  return 0;
}
