#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        vector<int> res;
        int flag=false;
        for(auto i=digits.rbegin();i!=digits.rend();i++){
            if(flag) res.push_back(*i);
            else{
                if(*i==9) res.push_back(0);
                else{
                    res.push_back((*i)+1);
                    flag=true;
                }
            }
        } 
        if(!flag) res.push_back(1);
        return vector<int>(res.rbegin(),res.rend());
    }
};


int main() {
    Solution solution;
    vector<int> digits = {1,2,3};
    vector<int> a = solution.plusOne(digits) ;
    cout << 1;
    return 0;
}