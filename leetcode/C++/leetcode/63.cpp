#include<bits/stdc++.h>
using namespace std;


class Solution {
public:
    int dp[101][101]={0};
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        return fun(obstacleGrid,0,0);
    }
    int fun(vector<vector<int>>& obstacleGrid,int x,int y){
        if(dp[x][y]>0) return dp[x][y];
        else if(x==obstacleGrid.size() || y==obstacleGrid[0].size()) return 0;
        else if(obstacleGrid[x][y]==1) dp[x][y]=0;
        else if(x==obstacleGrid.size()-1 && y==obstacleGrid[0].size()-1) dp[x][y]=1;
        else dp[x][y]=fun(obstacleGrid,x+1,y)+fun(obstacleGrid,x,y+1);
        return dp[x][y];
    }
};


int main() {
    Solution s;
    vector<vector<int>> obstacleGrid = {{1,3,1},{1,5,1},{4,2,1}};
    int a = s.uniquePathsWithObstacles(obstacleGrid) ;
    cout << a;
    return 0;
}