#include<bits/stdc++.h>
using namespace std;


class Solution {
public:
    int dp[100][100]={0};
    int uniquePaths(int m, int n) {
        if(dp[m][n]>0) return dp[m][n];
        if(m<=1 || n<=1) return 1;
        dp[m][n]=uniquePaths(m-1,n)+uniquePaths(m,n-1);
        return dp[m][n];
    }
};


int main() {
    Solution s;

    int a = s.uniquePaths(51, 9) ;
    cout << a;
    return 0;
}