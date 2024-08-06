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
    ListNode* oddEvenList(ListNode* head) {
        ListNode s_head,d_head;
        ListNode *s=&s_head,*d=&d_head;
        int len=0;
        while(head!=nullptr){
            len++;
            if(len%2) {
                s->next=head;
                s=s->next;
                head=head->next;
                s->next=nullptr;
            }
            else{
                d->next=head;
                d=d->next;
                head=head->next;
                d->next=nullptr;
            }
        }
        s->next=d_head.next;
        return s_head.next;
    }
};

int main() {
    Solution s;
    ListNode* node0 = new ListNode(5);
    ListNode* node1 = new ListNode(4,node0);
    ListNode* node2 = new ListNode(3,node1);
    ListNode* node3 = new ListNode(2,node2);
    ListNode* node4 = new ListNode(1,node3);
    
    ListNode* a = s.oddEvenList(node4) ;
    cout << 1;
    return 0;
}
