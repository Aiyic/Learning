#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    string gcdOfStrings(string str1, string str2) {
        string *longstr, *shortstr;
        if(str1.length()>str2.length()){
            longstr = &str1;
            shortstr = &str2;
        }
        else{
            longstr = &str2;
            shortstr = &str1;
        }
        for(int i=shortstr->length();i>0;i--){
            if(shortstr->length()%i || longstr->length()%i) continue;
            string pubstr(str1,0,i);
            bool flag = true;
            for(int j=0;j<shortstr->length()/i;j++){
                if(pubstr != string(*shortstr,j*i,i)){
                    flag = false;
                    break;
                }
            }
            if(!flag) continue;
            for(int j=0;j<longstr->length()/i;j++){
                if(pubstr != string(*longstr,j*i,i)){
                    flag = false;
                    break;
                } 
            }
            if(flag) return pubstr;
        }
        return "";
    }
};



int main() {
    Solution s;
    string a = s.gcdOfStrings("ABCABC","ABC") ;
    cout << a;
    return 0;
}
