
#include <bits/stdc++.h>
using namespace std;

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  explicit ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
  ListNode *reverseBetween(ListNode *head, int left, int right) {
    auto *dummy = new ListNode(0, head);
    ListNode *p = dummy;
    while (left > 1) {
      p = p->next;
      left--;
      right--;
    } // p.next指向反转位置开始的节点
    ListNode *tail = p;

    ListNode *list1 = dummy->next;
    auto *dummy2 = new ListNode(0, p->next);
    p->next = nullptr;

    p = dummy2;
    while (right > 0) {
      p = p->next;
      right--;
    } // p.next指向节点三

    auto *dummy3 = new ListNode(0, p->next);
    p->next = nullptr;

    p = dummy2->next;
    dummy2->next = nullptr;
    ListNode *tail2 = p;
    while (p != nullptr) {
      ListNode *tmp = p;
      p = p->next;
      tmp->next = dummy2->next;
      dummy2->next = tmp;
    }

    tail->next = dummy2->next;
    tail2->next = dummy3->next;

    p = dummy->next;
    delete dummy;
    delete dummy2;
    delete dummy3;
    return p;
  }
};

int main() {
  Solution s;

  auto *node0 = new ListNode(2);
  auto *node1 = new ListNode(5);
  auto *node2 = new ListNode(2, node1);
  auto *node3 = new ListNode(3, node2);
  auto *node4 = new ListNode(4, node3);
  auto *node5 = new ListNode(1, node4);

  auto *a = s.reverseBetween(node5, 2, 4);
  cout << 1;
  return 0;
}
