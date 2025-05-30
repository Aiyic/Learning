#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    string decodeString(string s) {
        int i=0;
        string res="";
        bool flag=true;

        while(i<s.length()){
            if(s[i]>='0' && s[i]<='9'){
                flag = false;
                int x=0;
                while(s[i]>='0' && s[i]<='9') {
                    x=x*10+s[i]-'0';
                    i++;
                }
                if(s[i]=='[') i++;
                string subs="";
                int left=1,right=0;
                while(1) {
                    if(s[i]=='[') left++;
                    if(s[i]==']') right++;
                    if(left==right) break;
                    subs+=s[i];
                    i++;
                }
                if(s[i]==']') i++;
                for(;x>0;x--){
                    res+=subs;
                }
            }
            else res+=s[i++];
        }
        if(flag) return res;
        else return decodeString(res);
    }
};

int main() {
    Solution s;
    string a=s.decodeString("3[a2[c]]") ;
    cout << 1;
    return 0;
}
