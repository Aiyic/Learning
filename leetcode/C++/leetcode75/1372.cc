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
    int maxhigh=0;
    int longestZigZag(TreeNode* root) {
        longestZigZag(root, -1, 0);
        longestZigZag(root, 1, 0);
        return maxhigh-1;
    }

    void longestZigZag(TreeNode* root, int rootisleft, int high) {
        maxhigh = max(maxhigh, high);
        int len=0;
        if(root){
            if(rootisleft==1){
                longestZigZag(root->left, 1, 1);
                longestZigZag(root->right, -1, high+1);
            }
            else{
                longestZigZag(root->left, 1, high+1);
                longestZigZag(root->right, -1, 1);
            }
        }
    }
};

int main() {
    Solution s;
    TreeNode* node0 = new TreeNode(7);
    TreeNode* node1 = new TreeNode(2);
    TreeNode* node2 = new TreeNode(11,node0,node1);
    TreeNode* node3 = new TreeNode(4,node2,nullptr);
    TreeNode* node4 = new TreeNode(13);
    TreeNode* node5 = new TreeNode(5);
    TreeNode* node6 = new TreeNode(1);
    TreeNode* node7 = new TreeNode(4,node5,node6);
    TreeNode* node8 = new TreeNode(8,node4,node7);
    TreeNode* node9 = new TreeNode(5,node3,node8);


    auto a = s.longestZigZag(node9) ;
    cout << 1;
    return 0;
}
