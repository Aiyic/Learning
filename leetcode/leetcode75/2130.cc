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
    int pairSum(ListNode* head) {
        ListNode *lefthead,*righthead;
        lefthead=righthead=head;
        head=head->next;
        int len=1;
        while(head!=nullptr){
            head=head->next;
            len++;
            if(len%2) righthead=righthead->next;
        }
        head=righthead;
        righthead=righthead->next;
        head->next=nullptr;
        lefthead=reverseList(lefthead);
        int maxv=INT_MIN;
        while(lefthead!=nullptr){
            maxv=max(maxv,lefthead->val+righthead->val);
            lefthead=lefthead->next;
            righthead=righthead->next;
        }
        return maxv;
    }
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
    ListNode* node1 = new ListNode(4);
    ListNode* node2 = new ListNode(3,node1);
    ListNode* node3 = new ListNode(2,node2);
    ListNode* node4 = new ListNode(1,node3);
    
    int a = s.pairSum(node4) ;
    cout << 1;
    return 0;
}
