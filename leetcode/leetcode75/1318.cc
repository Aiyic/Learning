#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minFlips(int a, int b, int c) {
        bool aa[32],bb[32],cc[32];
        for(int i=31; i>=0; --i){
            aa[i] = a%2; a/=2;
            bb[i] = b%2; b/=2;
            cc[i] = c%2; c/=2;
        }
        int res=0;
        for(int i=0; i<32; ++i){
            if((aa[i]|bb[i]) == cc[i]) continue;
            else{
                if(cc[i]) 
                    res += 1;
                else 
                    res = res + aa[i] + bb[i];
            }
        }
        return res;
    }
};


int main() {
    Solution s;
    auto a = s.minFlips(2,6,5) ;
    cout << a;
    return 0;
}
