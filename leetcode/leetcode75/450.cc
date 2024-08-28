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
    TreeNode* deleteNode(TreeNode* root, int key) {
        if(nullptr == root) {}
        else if(root->val < key){
            root->right=deleteNode(root->right,key);
        }
        else if(root->val > key){
            root->left=deleteNode(root->left,key);
        }
        else if(root->val == key){
            if(nullptr == root->left && nullptr == root->right){
                return nullptr;
            }
            else if( nullptr == root->left ){
                return root->right;
            }
            else if( nullptr == root->right ){
                return root->left;
            }
            else{
                TreeNode* min_r_node=root->right;
                while(min_r_node->left) min_r_node=min_r_node->left;
                min_r_node->right = deleteNode(root->right, min_r_node->val);
                min_r_node->left=root->left;
                root=min_r_node;    
            }
        }
        return root;
    }
};

int main() {
    Solution s;
    TreeNode* node0 = new TreeNode(2);
    TreeNode* node1 = new TreeNode(4);
    TreeNode* node2 = new TreeNode(3,node0,node1);
    TreeNode* node3 = new TreeNode(7);
    TreeNode* node4 = new TreeNode(6,nullptr,node3);
    TreeNode* node5 = new TreeNode(5,node2,node4);

    auto a = s.deleteNode(node5, 3) ;
    cout << 1;
    return 0;
}
