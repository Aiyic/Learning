#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    string addBinary(string a, string b) {
        if(b.length() > a.length()) swap(a, b);
        auto ap = a.rbegin(), bp = b.rbegin();
        int up = 0;
        string res = "";
        int i;
        for(i=0;i<b.length();i++) {
            int num = *ap - '0' + *bp - '0' + up;
            up = num / 2;
            res = (char)(num % 2 + '0') + res;
            ap++;
            bp++;
        }
        for(;i<a.length();i++){
            int num = *ap - '0' + up;
            up = num / 2;
            res = (char)(num % 2 + '0') + res;
            ap++;
        }
        if(up) res = '1' + res;
        return res;
    }
};


int main() {
    Solution solution;
    string a="111";
    string b="110000";
    string s = solution.addBinary(a,b) ;
    cout << 1;
    return 0;
}