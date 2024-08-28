
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

    vector<TreeNode*> generateTrees(int n) {
        return generateTrees(1,n);
    }

    vector<TreeNode*> generateTrees(int left, int right) {
        if(left>right) return {};
        if(left==right) {
            vector<TreeNode*> res;
            res.emplace_back(new TreeNode(left));
            return res;
        }
        vector<TreeNode*> res;
        for(int i=left;i<=right;i++){
            if(i==right){
                auto lefttrees = generateTrees(left,i-1);
                for(auto lefttree : lefttrees){
                    res.emplace_back(new TreeNode(i));
                    res.back()->left=lefttree;
                }
            }
            else if(i==left){
                auto righttrees = generateTrees(i+1,right);
                for(auto righttree : righttrees){
                    res.emplace_back(new TreeNode(i));
                    res.back()->right=righttree;
                }
            }
            else{
                auto lefttrees = generateTrees(left,i-1);
                auto righttrees = generateTrees(i+1,right);
                for(auto lefttree : lefttrees){
                    for(auto righttree : righttrees){
                        res.emplace_back(new TreeNode(i));
                        res.back()->left=lefttree;
                        res.back()->right=righttree;
                    }
                }
            }
        }
        return res;
    }
};

int main() {
    Solution s;


    auto a = s.generateTrees(3) ;
    cout << 1;
    return 0;
}
