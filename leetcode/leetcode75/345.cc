#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    string reverseVowels(string s) {
        vector<int> idx;
        unordered_set<char> aeiou = {'a','e','i','o','u',
                                     'A','E','I','O','U'};
        unordered_set<int> idx2;
        string res="";
        for(int i=0;i<s.length();i++){
            if(aeiou.find(s[i])!=aeiou.end()){
                idx.push_back(i);
                idx2.insert(i);
            }
        }
        reverse(idx.begin(),idx.end());
        int id=0;
        for(int i=0;i<s.length();i++){
            if(idx2.find(i)!=idx2.end())
                res += s[idx[id++]];
            else
                res += s[i];
        }
        return res;
    }
};


int main() {
    Solution s;
    string a = s.reverseVowels("") ;
    cout << 1;
    return 0;
}
