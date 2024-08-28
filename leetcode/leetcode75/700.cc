#include<bits/stdc++.h>

using namespace std;

/*
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
    TreeNode* searchBST(TreeNode* root, int val) {
        if(root==nullptr) return nullptr;

        if(root->val > val) return searchBST(root->left,val);
        else if(root->val < val) return searchBST(root->right,val);
        else return root;
    }
};

int main() {
    Solution s;
    TreeNode* node0 = new TreeNode(1);
    TreeNode* node1 = new TreeNode(3);
    TreeNode* node2 = new TreeNode(2,node0,node1);
    TreeNode* node3 = new TreeNode(7);
    TreeNode* node4 = new TreeNode(4,node2,node3);

    auto a = s.searchBST(node4, 2) ;
    cout << 1;
    return 0;
}
