#include <bits/stdc++.h>
#include <cstddef>
using namespace std;

class Node {
public:
  int val;
  Node *left;
  Node *right;
  Node *next;

  Node() : val(0), left(nullptr), right(nullptr), next(nullptr) {}

  explicit Node(int _val)
      : val(_val), left(nullptr), right(nullptr), next(nullptr) {}

  Node(int _val, Node *_left, Node *_right, Node *_next)
      : val(_val), left(_left), right(_right), next(_next) {}
};

class Solution {
public:
  static Node *connect(Node *root) {
    deque<Node *> now;
    deque<Node *> next;

    Node *last = nullptr;
    if (root != nullptr) {
      now.push_back(root);
      while (!now.empty()) {
        auto *x = now.front();
        now.pop_front();

        if (last != nullptr) {
          last->next = x;
        }
        last = x;

        if (x->left != nullptr) {
          next.push_back(x->left);
        }
        if (x->right != nullptr) {
          next.push_back(x->right);
        }
        if (now.empty()) {
          last = nullptr;
          now.swap(next);
        }
      }
    }
    return root;
  }
};

int main() {
  auto *n1 = new Node(7);
  auto *n2 = new Node(2);
  auto *n3 = new Node(11, n1, n2, nullptr);
  auto *x = Solution::connect(n3);
  cout << x;
  return 0;
}
