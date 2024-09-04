#include <iostream>

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode* sortList(ListNode* head) {
        // 如果链表为空或只有一个节点，直接返回
        if (!head || !head->next) return head;

        // 使用快慢指针找到链表的中间节点
        ListNode* mid = getMid(head);
        ListNode* left = sortList(head); // 排序左半部分
        ListNode* right = sortList(mid);  // 排序右半部分

        // 合并已排序的链表
        return merge(left, right);
    }

private:
    // 找到链表的中间节点
    ListNode* getMid(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head->next;

        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        ListNode* mid = slow->next;
        slow->next = nullptr; // 切断链表
        return mid;
    }

    // 合并两个已排序的链表
    ListNode* merge(ListNode* l1, ListNode* l2) {
        ListNode dummy(0);
        ListNode* tail = &dummy;

        while (l1 && l2) {
            if (l1->val < l2->val) {
                tail->next = l1;
                l1 = l1->next;
            } else {
                tail->next = l2;
                l2 = l2->next;
            }
            tail = tail->next;
        }

        // 如果还有剩余的节点，直接连接到尾部
        tail->next = l1 ? l1 : l2;

        return dummy.next;
    }
};

// 测试代码
int main() {
    ListNode* head = new ListNode(4);
    head->next = new ListNode(2);
    head->next->next = new ListNode(1);
    head->next->next->next = new ListNode(3);

    Solution solution;
    ListNode* sortedHead = solution.sortList(head);

    // 打印排序后的链表
    ListNode* current = sortedHead;
    while (current) {
        std::cout << current->val << " -> ";
        current = current->next;
    }
    std::cout << "nullptr" << std::endl;

    return 0;
}