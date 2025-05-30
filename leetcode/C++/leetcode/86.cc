
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
    explicit ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* partition(ListNode* head, int x) {
        auto* small_node_dummy = new ListNode();
        auto* large_node_dummy = new ListNode();
        ListNode* sp = small_node_dummy;
        ListNode* lp = large_node_dummy;

        while(head != nullptr){
            if(head->val<x){
                sp->next = head;
                sp = sp->next;
                head = head->next;
                sp->next=nullptr;
            }
            else{
                lp->next = head;
                lp = lp->next;
                head = head->next;
                lp->next=nullptr;
            }
        }
        sp->next = large_node_dummy->next;
        head = small_node_dummy->next;
        delete small_node_dummy;
        delete large_node_dummy;
        return head;
    }
};


int main() {
    Solution s;

    auto* node0 = new ListNode(2);
    auto* node1 = new ListNode(5,node0);
    auto* node2 = new ListNode(2,node1);
    auto* node3 = new ListNode(3,node2);
    auto* node4 = new ListNode(4,node3);
    auto* node5 = new ListNode(1,node4);
    
    auto *a = s.partition(node5, 3) ;
    cout << 1;
    return 0;
}
