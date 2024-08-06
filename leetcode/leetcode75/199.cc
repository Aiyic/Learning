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
    
    deque<TreeNode*> level;
    vector<int> res;
    vector<int> rightSideView(TreeNode* root) {
        if(root){
            level.push_back(root);
            lfs();
        }
        return res;
    }

    void lfs(){
        res.push_back(level.back()->val);

        int len=level.size();
        for(int i=0;i<len;i++){
            if(level.front()->left)
                level.push_back(level.front()->left);
            if(level.front()->right)
                level.push_back(level.front()->right);
            level.pop_front();
        }

        if(level.size()>0) lfs();
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


    auto a = s.rightSideView(node8) ;
    cout << 1;
    return 0;
}
