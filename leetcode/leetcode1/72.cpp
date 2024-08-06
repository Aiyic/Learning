/*
 * @lc app=leetcode.cn id=72 lang=cpp
 *
 * [72] 编辑距离
 *
 * https://leetcode.cn/problems/edit-distance/description/
 *
 * algorithms
 * Hard (62.80%)
 * Likes:    3165
 * Dislikes: 0
 * Total Accepted:    405.2K
 * Total Submissions: 645K
 * Testcase Example:  '"horse"\n"ros"'
 *
 * 给你两个单词 word1 和 word2， 请返回将 word1 转换成 word2 所使用的最少操作数  。
 * 
 * 你可以对一个单词进行如下三种操作：
 * 
 * 
 * 插入一个字符
 * 删除一个字符
 * 替换一个字符
 * 
 * 
 * 
 * 
 * 示例 1：
 * 
 * 
 * 输入：word1 = "horse", word2 = "ros"
 * 输出：3
 * 解释：
 * horse -> rorse (将 'h' 替换为 'r')
 * rorse -> rose (删除 'r')
 * rose -> ros (删除 'e')
 * 
 * 
 * 示例 2：
 * 
 * 
 * 输入：word1 = "intention", word2 = "execution"
 * 输出：5
 * 解释：
 * intention -> inention (删除 't')
 * inention -> enention (将 'i' 替换为 'e')
 * enention -> exention (将 'n' 替换为 'x')
 * exention -> exection (将 'n' 替换为 'c')
 * exection -> execution (插入 'u')
 * 
 * 
 * 
 * 
 * 提示：
 * 
 * 
 * 0 <= word1.length, word2.length <= 500
 * word1 和 word2 由小写英文字母组成
 * 
 * 
 */
#include<bits/stdc++.h>
using namespace std;
// @lc code=start
class Solution {
public:
    string wd1,wd2;
    int n1,n2;
    int res[500][500]={0};
    int minDistance(string word1, string word2) {
        wd1=word1;
        wd2=word2;
        n1=word1.size();
        n2=word2.size();
        return distance(0,0);
    }

    int distance(int i, int j){
        if(j>=n2) return n1-i;
        if(i>=n1) return n2-j;
        
        if(res[i][j]) return res[i][j];
        auto idx = string(wd1,i).find(wd2[j])+i;
        res[i][j] = min(distance(i,j+1)+1,distance(i+1,j+1)+1);
        
        if(idx!=wd1.npos && idx>=i){
            res[i][j] = min(res[i][j],distance(idx+1,j+1)+(int)idx-i);
        }
        return res[i][j];
    }
};
// @lc code=end

int main(){
    Solution solution;
    string s1="";
    string s2="utionnn";
    int a = solution.minDistance(s1,s2);
    cout << a << endl;
}


