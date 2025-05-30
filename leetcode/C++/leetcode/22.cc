#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<string> res={};
    vector<string> generateParenthesis(int n) {
        fun("",n,n);
        return res;
    }
    void fun(string str, int left, int right){
        if(left>right) return;
        else if(left==0) {
            while(right--){
                str+=')';
            }
            res.push_back(str);
        }
        else if(right==0) {
            while(left--){
                str+=')';
            }
            res.push_back(str);
        }
        else {
            fun(str+')',left,right-1);
            fun(str+'(',left-1,right);
        }
    }
};

int main() {
    Solution x;
    vector<string> a = x.generateParenthesis(2);
    return 0;
}
