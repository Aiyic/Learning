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

    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        deque<TreeNode*> pathp,pathq;
        bool flag=false;
        dfs(pathp,root,p,flag);
        flag=false;
        dfs(pathq,root,q,flag);
        TreeNode* res;
        while(!pathp.empty() && !pathq.empty()){
            if(pathp.front()==pathq.front()) {
                res=pathp.front();
                pathp.pop_front();
                pathq.pop_front();
            }
            else break;
        }
        return res;
    }

    void dfs(deque<TreeNode*>& res, TreeNode* root, TreeNode* s, bool& flag){
        res.push_back(root);
        if(root!=s){
            if(root->left) {
                dfs(res,root->left,s,flag);
            }
            if(flag) return;
            if(root->right) {
                dfs(res,root->right,s,flag);
            }
            if(flag) return;
            res.pop_back();
        }
        else flag=true;
    }
};


int main() {
    Solution s;
    TreeNode* node0 = new TreeNode(7);
    TreeNode* node1 = new TreeNode(4);
    TreeNode* node2 = new TreeNode(6);
    TreeNode* node3 = new TreeNode(2,node0,node1);
    TreeNode* node4 = new TreeNode(5,node2,node3);
    TreeNode* node5 = new TreeNode(0);
    TreeNode* node6 = new TreeNode(8);
    TreeNode* node7 = new TreeNode(1,node5,node6);
    TreeNode* node8 = new TreeNode(3,node4,node7);


    auto a = s.lowestCommonAncestor(node8,node4,node1) ;
    cout << 1;
    return 0;
}
