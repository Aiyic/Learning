#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isSubsequence(string s, string t) {
        int i=0,j=0;
        while(j<t.length()){
            if(s[i]==t[j]){
                i++;j++;
            }
            else j++;
        }
        if(i==s.length()) return true;
        else return false;
    }
};

int main() {
    Solution s;
    vector<int> nums={0,1,0,3,12};
    bool a=s.isSubsequence("axc","ahbgdc") ;
    cout << 1;
    return 0;
}
