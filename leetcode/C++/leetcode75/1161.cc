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

    int maxvalue=INT_MIN;
    int maxlevel=0;
    int nowlevel=0;


    int maxLevelSum(TreeNode* root) {
        if(root){
            level.push_back(root);
            lfs();
        }
        return maxlevel;
    }

    void lfs(){
        int value=0;
        nowlevel++;

        int len=level.size();
        for(int i=0;i<len;i++){
            auto node = level.front();
            value += node->val;
            if(node->left)
                level.push_back(node->left);
            if(node->right)
                level.push_back(node->right);
            level.pop_front();
        }
        if(value>maxvalue) {
            maxvalue=value;
            maxlevel=nowlevel;
        }
    
        if(level.size()>0) lfs();
    }

};

int main() {
    Solution s;
    TreeNode* node0 = new TreeNode(-32127);
    TreeNode* node1 = new TreeNode(-89388,nullptr,node0);
    TreeNode* node2 = new TreeNode(98693);
    TreeNode* node3 = new TreeNode(2,node2,node1);
    TreeNode* node4 = new TreeNode(989,nullptr,node3);

    auto a = s.maxLevelSum(node4) ;
    cout << 1;
    return 0;
}
