#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int lengthOfLastWord2(string s) {
        int i=s.length()-1;
        while(i>=0 && s[i]==' ') i--;
        int x=0;
        for(;i>=0;i--){
            if(s[i]==' ') break;
            x++;
        }
        return x;
    }

    int lengthOfLastWord(string s) {
        auto c=s.rbegin();
        for(;c!=s.rend();c++){
            if((*c)!=' ') break;
        }
        int x=0;
        for(;c!=s.rend();c++,x++){
            if((*c)==' ') break;
        }
        return x;
    }
};


int main() {
    Solution solution;
    string s="   fly me   to   the moon  ";
    int a = solution.lengthOfLastWord(s) ;
    cout << a;
    return 0;
}
