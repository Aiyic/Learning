#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int numTilings(int n) {
        vector<int> dp(n+4,-1);
        dp[1]=1;
        dp[2]=2;
        dp[3]=5;
        dp[4]=11;
        static function<int(int)> fun;
        static function<int(float)> fun2;
        static auto mod = [](int x){
            return x % 1000000007;
        };

        fun = [&](int k){
            if(k<=4) return dp[k];
            if(dp[k]>=0) return dp[k];
            // fun(k-1) = 以竖结尾
            // fun(k-2) = 以两横结尾
            // fun2(-1.5+k) = 以三角结尾，上下对称乘2
            dp[k] = mod(mod(fun(k-1) + fun(k-2)) + mod(fun2(-1.5+k)*2));
            return dp[k];
        };
        vector<int> dp2(n+4,-1);
        fun2 = [&](float k){
            if(k==1.5) return 1;
            if(dp2[(int)k]>=0) return dp2[(int)k];
            // fun(k-1.5) = 以相匹配的三角结尾
            // fun2(k-1) = 加入一横，结尾形状还是三角
            dp2[(int)k]=mod(fun(k-1.5) + fun2(k-1));
            return dp2[(int)k];
        };

        return fun(n);
    }
};

int main() {
    Solution s;
    auto a = s.numTilings(5);
    cout << a;
    return 0;
}
