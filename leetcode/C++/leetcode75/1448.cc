#include<bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    int n=0;
    int goodNodes(TreeNode* root) { // 返回根到当前节点的最大值
        fun(root, root->val);
        return n;
    }

    void fun(TreeNode* node, int key){
        if(node->val>=key) n++;
        if(node->left) fun(node->left, max(key, node->left->val));
        if(node->right) fun(node->right, max(key, node->right->val));
    }
};



int main() {
    Solution s;
    TreeNode* node0 = new TreeNode(3);
    TreeNode* node1 = new TreeNode(1);
    TreeNode* node2 = new TreeNode(5);
    TreeNode* node3 = new TreeNode(1,node0,nullptr);
    TreeNode* node4 = new TreeNode(4,node1,node2);
    TreeNode* node5 = new TreeNode(3,node3,node4);

    
    // TreeNode* node9 = new TreeNode(6);
    // TreeNode* node10 = new TreeNode(7);
    // TreeNode* node11 = new TreeNode(4);
    // TreeNode* node12 = new TreeNode(2,node10,node11);
    // TreeNode* node13 = new TreeNode(5,node9,node12);
    // TreeNode* node14 = new TreeNode(9);
    // TreeNode* node15 = new TreeNode(8);
    // TreeNode* node16 = new TreeNode(1,node14,node15);
    // TreeNode* node17 = new TreeNode(3,node13,node16);
    
    bool a = s.goodNodes(node5) ;
    cout << 1;
    return 0;
}
