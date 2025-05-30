
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int tribonacci(int n) {
        vector<int> dp(n+3,-1);
        dp[0]=0;
        dp[1]=1;
        dp[2]=1;

        static function<int(int)> fun = [&](int k){
            if(dp[k]>=0) return dp[k];

            dp[k]=fun(k-1)+fun(k-2)+fun(k-3);
            return dp[k];
        };

        return fun(n);
    }
};

int main() {
    Solution s;
    auto a = s.tribonacci(0) ;
    cout << 1;
    return 0;
}
