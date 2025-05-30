#include<bits/stdc++.h>
using namespace std;


class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        vector<vector<int>> dp(grid.size(),vector<int>(grid[0].size(),0));
        return fun(dp, grid,0,0);
    }
    int fun(vector<vector<int>>& dp, vector<vector<int>>& grid,int x,int y){
        if(dp[x][y]>0) return dp[x][y];
        else if(x==grid.size() || y==grid[0].size()) return INT_MAX;
        else if(x==grid.size()-1 && y==grid[0].size()-1) dp[x][y]=grid[x][y];
        else dp[x][y]=min(fun(dp,grid,x+1,y),fun(dp,grid,x,y+1))+grid[x][y];
        return dp[x][y];
    }
};


int main() {
    Solution s;
    vector<vector<int>> grid = {{1,3,1},{1,5,1},{4,2,1}};
    int a = s.minPathSum(grid) ;
    cout << a;
    return 0;
}