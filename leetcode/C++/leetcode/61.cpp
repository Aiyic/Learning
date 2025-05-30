#include<bits/stdc++.h>
using namespace std;


// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
 
class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if(head==nullptr) return head;
        ListNode* newhead=head; 
        ListNode* last=nullptr;
        int n=0;
        while(newhead!=nullptr){
            last=newhead;
            newhead=newhead->next;
            n++;
        }
        k=k%n;
        newhead=head;
        if(k==0) return head;
        last->next=head;
        for(int x=0; x<n-k; x++){
            last=newhead;
            newhead=newhead->next;
        }
        last->next=nullptr;
        return newhead;
    }
};


int main() {
    Solution s;
    ListNode* node5=new ListNode(5, nullptr);
    ListNode* node4=new ListNode(4, node5);
    ListNode* node3=new ListNode(3, node4);
    ListNode* node2=new ListNode(2, node3);
    ListNode* node1=new ListNode(1, node2);
    ListNode* a = s.rotateRight(node1, 2) ;
    cout << a;
    return 0;
}