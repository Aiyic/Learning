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
    vector<string> results;
    vector<string> binaryTreePaths(TreeNode* root) {
        fun("",root);
        return results;
    }   
    void fun(string str, TreeNode* root) {
        if(str == "") str = to_string(root->val);
        else str = str + "->" + to_string(root->val);
        
        if(root->left==nullptr && root->right==nullptr) 
            results.emplace_back(str);
        else{
            if(root->left) fun(str,root->left);
            if(root->right) fun(str,root->right);
        }
    }
};

int main() {
    Solution s;
    TreeNode* node0 = new TreeNode(5);
    TreeNode* node1 = new TreeNode(2,nullptr,node0);
    TreeNode* node2 = new TreeNode(3);
    TreeNode* node3 = new TreeNode(1,node1,node2);
    
    auto a = s.binaryTreePaths(node3) ;
    cout << 1;
    return 0;
}
