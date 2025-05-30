#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool closeStrings(string word1, string word2) {
        unordered_map<char,int> chars1,chars2;
        vector<bool> chcount1(26),chcount2(26);
        for(char &c : word1){
            chcount1[c-'a']=true;
            if(chars1.count(c)) chars1[c]++;
            else chars1[c]=1;
        }
        for(char &c : word2){
            chcount2[c-'a']=true;
            if(chars2.count(c)) chars2[c]++;
            else chars2[c]=1;
        }
        for(int i=0;i<26;i++){
            if(chcount1[i]^chcount2[i]) return false;
        }
        multiset<int> charset;
        for(auto &c : chars1){
            charset.insert(c.second);
        }
        for(auto &c : chars2){
            auto it = charset.find(c.second);
            if(it==charset.end()) return false;
            charset.erase(it);
        }
        if(charset.empty()) return true;
        else return false;
    }
};

int main() {
    Solution s;
    vector<int> nums1={1,2,3,4};
    vector<int> nums2={1,2,3,4};
    bool a = s.closeStrings("cabbba","abbccc");
    cout << 1;
    return 0;
}
