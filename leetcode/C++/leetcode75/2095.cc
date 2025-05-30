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
    ListNode* deleteMiddle(ListNode* head) {
        ListNode *last,*mid,*tail;
        last=head;
        mid=head;
        tail=head->next;
        int len=1;
        while(tail!=nullptr){
            tail=tail->next;
            len++;
            if(len%2==0){
                last=mid;
                mid=mid->next;
            }
        }
        if(len==1) return nullptr;
        last->next=last->next->next;
        return head;
    }
};

int main() {
    Solution s;
    ListNode* node1 = new ListNode(4);
    ListNode* node2 = new ListNode(3,node1);
    ListNode* node3 = new ListNode(2,node2);
    ListNode* node4 = new ListNode(1,node3);
    
    ListNode* a = s.deleteMiddle(node4) ;
    cout << 1;
    return 0;
}
