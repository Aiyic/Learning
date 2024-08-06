#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> countBits(int n) {
        // nlgn
        vector<int> res(n+1);
        for(int i=0;i<=n;++i){
            int num=i;
            while(num){
                if(num%2 != 0) res[i]++;
                num = num >> 1;
            }
        }
        return res;
    }

    vector<int> countBits2(int n) {
        // n
        vector<bool> num(16,false);
        vector<int> res(n+1,0);
        int x=0;
        for(int i=1;i<=n;++i){
            int idx=0;
            while(num[idx]==true) {
                num[idx]=false;
                x--;idx++;
            }
            x++;num[idx]=true;
            
            res[i]=x;
        }
        return res;
    }

    vector<int> countBits3(int n) {
        vector<int> bits(n+1);
        for(int i=0;i<=n;i++)
        {
            bits[i]=bits[i>>1]+(i&1);
        }
        return bits;
    }
};

int main() {
    Solution s;
    auto a = s.countBits2(2);
    cout << 1;
    return 0;
}
