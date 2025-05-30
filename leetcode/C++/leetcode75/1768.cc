#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    string mergeAlternately(string word1, string word2) {
        string *longstr;
        int len;
        if(word1.length()>word2.length()){
            len = word2.length();
            longstr = &word1;
        }
        else{
            len = word1.length();
            longstr = &word2;
        }
        string res="";
        for(int i=0;i<len;i++){
            res = res+word1[i]+word2[i];
        }
        for(int i=len;i<longstr->length();i++){
            res = res + (*longstr)[i];
        }
        return res;
    }
};



int main() {
    Solution s;
    string a = s.mergeAlternately("abc","pqr") ;
    cout << a;
    return 0;
}
