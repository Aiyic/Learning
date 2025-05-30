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
    int maxDepth(TreeNode* root) {
        if(root==nullptr) return 0;
        return 1+max(maxDepth(root->left),maxDepth(root->right));
    }
};

int main() {
    Solution s;
    TreeNode* node0 = new TreeNode(5);
    TreeNode* node1 = new TreeNode(4);
    TreeNode* node2 = new TreeNode(3,node0,node1);
    TreeNode* node3 = new TreeNode(2);
    TreeNode* node4 = new TreeNode(1,node3,node2);
    
    int a = s.maxDepth(node4) ;
    cout << 1;
    return 0;
}
