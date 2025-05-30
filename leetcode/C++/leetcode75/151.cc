#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    string reverseWords(string s) {
        vector<string> rec;
        int idx=0;
        while(idx<s.length()){
            int len=0;
            while(s[idx]==' ') idx++;
            while(idx+len<s.length() && s[idx+len]!=' ') len++;
            if(len) rec.emplace_back(string(s,idx,len));
            idx+=len;
        }
        string res="";
        for(auto str=rec.rbegin();str!=rec.rend();str++){
            res = res+*str+" ";
        }
        res.erase(res.end()-1);
        return res;
    }
};

int main() {
    Solution s;
    string a = s.reverseWords("  hello world  ") ;
    cout << 1;
    return 0;
}
