
#include<bits/stdc++.h>
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
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
 
class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        ListNode* node=head;
        if(node==nullptr) return nullptr;
        while(node!=nullptr && node->val==val) node=node->next;
        if(node==nullptr) return nullptr;
        head=node;
        while(node->next!=nullptr){
            if(node->next->val==val){
                node->next=node->next->next;
            }
            else node=node->next;
        }
        return head;
    }
};

int main() {
    Solution s;

    ListNode* node1 = new ListNode(6);
    ListNode* node2 = new ListNode(5,node1);
    ListNode* node3 = new ListNode(4,node2);
    ListNode* node4 = new ListNode(3,node3);
    ListNode* node5 = new ListNode(6,node4);
    ListNode* node6 = new ListNode(2,node5);
    ListNode* node7 = new ListNode(1,node6);

    auto a = s.removeElements(node7, 6) ;
    cout << a;
    return 0;
}
