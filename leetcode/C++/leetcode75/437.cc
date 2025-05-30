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

// class Solution {
// public:
//     int num=0;
//     int target;
//     unordered_map<TreeNode*,vector<long long>> dp;
//     int pathSum(TreeNode* root, int targetSum) {
//         target=targetSum;
//         if(root==nullptr) return 0;
//         dp[root]={root->val};
//         if(root->val==targetSum) num++;
//         cacl(root);
//         return num;
//     }
//     void cacl(TreeNode* root){
//         auto &res = dp[root];
//         if(root->left) {
//             dp[root->left] = res;
//             dp[root->left].emplace_back(0);
//             int val = root->left->val;
//             int i=0;
//             for(auto &x : dp[root->left]){
//                 x+=val;
//                 if(x==target) num++;
//             }
//             cacl(root->left);
//         }
//         if(root->right) {
//             dp[root->right] = res;
//             dp[root->right].emplace_back(0);
//             int val = root->right->val;
//             int i=0;
//             for(auto & x : dp[root->right]){
//                 x+=val;
//                 if(x==target) num++;
//             }
//             cacl(root->right);
//         }
//     }
// };

class Solution {
public:
    int num=0;
    int target;

    int pathSum(TreeNode* root, int targetSum) {
        if(root==nullptr) return 0;
        unordered_multiset<long long> results;
        target=targetSum;
        dfs(results, root, 0);
        return num;
    }
    
    void dfs(unordered_multiset<long long> &results, TreeNode* root, long long value){
        long long prefix = value + root->val;

        auto c=results.count(prefix-target);
        if(c) num+=c;

        results.insert(prefix);
        if(prefix==target) num++;

        if(root->left) dfs(results, root->left, value+root->val); 
        if(root->right) dfs(results, root->right, value+root->val); 

        results.erase(results.find(prefix));
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

    TreeNode* node10 = new TreeNode(1);
    TreeNode* node11 = new TreeNode(1);
    TreeNode* node12 = new TreeNode(0,node10,node11);

    TreeNode* node13 = new TreeNode(1);

    TreeNode* node14 = new TreeNode(-1);
    TreeNode* node15 = new TreeNode(1,node14,nullptr);
    TreeNode* node16 = new TreeNode(3);
    TreeNode* node17 = new TreeNode(-2,node15,node16);
    TreeNode* node18 = new TreeNode(-2);
    TreeNode* node19 = new TreeNode(-3,node18,nullptr);
    TreeNode* node20 = new TreeNode(1,node17,node19);

    TreeNode* node21 = new TreeNode(1000000000);
    TreeNode* node22 = new TreeNode(1000000000,node21,nullptr);
    TreeNode* node23 = new TreeNode(1000000000,node22,nullptr);
    TreeNode* node24 = new TreeNode(294967296,node23,nullptr);
    TreeNode* node25 = new TreeNode(1000000000,node24,nullptr);
    TreeNode* node26 = new TreeNode(1000000000,node25,nullptr);


    auto a = s.pathSum(node26, 0) ;
    cout << 1;
    return 0;
}
