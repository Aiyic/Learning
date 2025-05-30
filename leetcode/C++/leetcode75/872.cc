#include<bits/stdc++.h>
using namespace std;

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

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
    bool leafSimilar(TreeNode* root1, TreeNode* root2) {
        stack<TreeNode*> leaf;
        queue<int> val;
        leaf.push(root1);
        while(!leaf.empty()){
            TreeNode* node = leaf.top();
            leaf.pop();
            if(node) {
                if(node->left==nullptr && node->right==nullptr ) 
                    val.push(node->val);
                leaf.push(node->left);
                leaf.push(node->right);
            }
        }
        leaf.push(root2);
        while(!leaf.empty()){
            TreeNode* node = leaf.top();
            leaf.pop();
            if(node) {
                if(node->left==nullptr && node->right==nullptr ) {
                    if(node->val == val.front()) val.pop();
                    else return false;
                }
                leaf.push(node->left);
                leaf.push(node->right);
            }
        }
        if(val.empty()) return true;
        else return false;
    }
};

int main() {
    Solution s;
    TreeNode* node0 = new TreeNode(6);
    TreeNode* node1 = new TreeNode(7);
    TreeNode* node2 = new TreeNode(5,node0,node1);
    TreeNode* node3 = new TreeNode(9);
    TreeNode* node4 = new TreeNode(8);
    TreeNode* node5 = new TreeNode(2,node3,node4);
    TreeNode* node6 = new TreeNode(4);
    TreeNode* node7 = new TreeNode(1,node6,node5);
    TreeNode* node8 = new TreeNode(1,node2,node7);
    
    TreeNode* node9 = new TreeNode(6);
    TreeNode* node10 = new TreeNode(7);
    TreeNode* node11 = new TreeNode(4);
    TreeNode* node12 = new TreeNode(2,node10,node11);
    TreeNode* node13 = new TreeNode(5,node9,node12);
    TreeNode* node14 = new TreeNode(9);
    TreeNode* node15 = new TreeNode(8);
    TreeNode* node16 = new TreeNode(1,node14,node15);
    TreeNode* node17 = new TreeNode(3,node13,node16);
    
    bool a = s.leafSimilar(node8, node17) ;
    cout << 1;
    return 0;
}
