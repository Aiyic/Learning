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
    ListNode* reverseList(ListNode* head) {
        ListNode* newhead=nullptr;
        while(head!=nullptr){
            ListNode* newnode;
            newnode=head;
            head=head->next;
            newnode->next=newhead;
            newhead = newnode;
        }
        return newhead;
    }
};

int main() {
    Solution s;
    ListNode* node0 = new ListNode(5);
    ListNode* node1 = new ListNode(4,node0);
    ListNode* node2 = new ListNode(3,node1);
    ListNode* node3 = new ListNode(2,node2);
    ListNode* node4 = new ListNode(1,node3);
    
    ListNode* a = s.reverseList(node4) ;
    cout << 1;
    return 0;
}
