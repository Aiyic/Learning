#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    string removeStars(string s) {
        string res="";
        for(auto &c : s){
            if(c=='*') res.pop_back();
            else res.push_back(c);
        }
        return res;
    }
};
int main() {
    Solution s;
    vector<vector<int>> grid={};
    string a=s.removeStars("ahbgdc") ;
    cout << 1;
    return 0;
}
