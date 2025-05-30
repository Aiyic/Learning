#include<bits/stdc++.h>
using namespace std;

/*
 * @lc app=leetcode.cn id=68 lang=cpp
 *
 * [68] 文本左右对齐
 */

// @lc code=start
class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<string> results;
        int i=0;
        while(i<words.size()){
            string res="";
            int length=-1;
            int begin=i;
            while(i<words.size()){
                if(length+words[i].length()+1<=maxWidth) 
                    length+=words[i].length()+1;
                else break;
                i++;
            }
            int end=i;
            
            int num=end-begin;
            int add0,add1;
            if(num==1){
                add0=maxWidth-length+1;
                add1=0;
            }
            else{
                add0=(maxWidth-length)/(num-1)+1;
                add1=(maxWidth-length)%(num-1);
            }
            if(i>=words.size()){
                for(int j=begin;j<end;j++){
                    res=res+words[j]+' ';
                }
                res=res+string(maxWidth,' ');
                results.push_back(string(res,0,maxWidth));
                break;
            }
            for(int j=begin;j<end;j++){
                res=res+words[j]+string(add0,' ');
                if(add1) {
                    res=res+' ';
                    add1--;
                }
            }
            results.push_back(string(res,0,maxWidth));
        }
        return results;
    }
};
// @lc code=end

int main() {
    Solution solution;
    vector<string> words={"What","must","be","acknowledgment","shall","be"};
    vector<string> s = solution.fullJustify(words,16) ;
    cout << 1;
    return 0;
}