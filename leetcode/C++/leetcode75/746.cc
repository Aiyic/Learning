
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        vector<int> dp(cost.size()+1,-1);
        dp[0]=dp[1]=0;
        // dp[i] 爬到i的最小花费

        static function<int(int)> climb = [&](int k){
            if(dp[k]>=0) return dp[k];

            dp[k]=min(climb(k-2)+cost[k-2], climb(k-1)+cost[k-1]);
            return dp[k];
        };
        
        return climb(cost.size());
    }
};


int main() {
    Solution s;
    vector<int> cost={10,15,20};
    auto a = s.minCostClimbingStairs(cost) ;
    cout << a;
    return 0;
}
