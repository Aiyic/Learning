#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool repeatedSubstringPattern(string s) {
        int n=s.length();
        hash<string> myhash;
        for(int i=1;i<=n/2;i++){
            bool flag=true;
            int h=myhash(string(s,0,i));
            // string s1=string(s,0,i);
            for(int j=i;j<=n-i;j+=i){
                // string s2=string(s,j,i);
                int h2=myhash(string(s,j,i));
                if(h2!=h){
                    flag=false;
                    break;
                }
            }
            if(flag) return true; 
        }
        return false;
    }
};



int main() {
    Solution s;
    string str="abab";
    bool a = s.repeatedSubstringPattern(str) ;
    cout << 2;
    return 0;
}
