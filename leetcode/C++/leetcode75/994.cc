#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int good=0;
        queue<pair<int,int>> bad;
        for(int i=0;i<grid.size();++i){
            for(int j=0;j<grid[0].size();++j){
                if(grid[i][j]==1) good++;
                else if(grid[i][j]==2) bad.emplace(i,j);
            }
        }
        int time=-1;
        if(bad.empty() && good>0) return -1;
        if(bad.empty() && good==0) return 0;

        while(!bad.empty()){
            int n=bad.size();
            time++;
            while(n--){
                auto t=bad.front();
                bad.pop();
                if(t.first>0 && grid[t.first-1][t.second]==1) {
                    bad.emplace(t.first-1,t.second);
                    grid[t.first-1][t.second]=2;
                    good--;
                }
                if(t.first<grid.size()-1 && grid[t.first+1][t.second]==1) {
                    bad.emplace(t.first+1,t.second);
                    grid[t.first+1][t.second]=2;
                    good--;
                }
                if(t.second>0 && grid[t.first][t.second-1]==1) {
                    bad.emplace(t.first,t.second-1);
                    grid[t.first][t.second-1]=2;
                    good--;
                }
                if(t.second<grid[0].size()-1 && grid[t.first][t.second+1]==1) {
                    bad.emplace(t.first,t.second+1);
                    grid[t.first][t.second+1]=2;
                    good--;
                }
            }
        }
        if(good==0) return time;
        else return -1;
    }
};





int main() {
    Solution solution;
    vector<vector<int>> grid={{2,1,1},{1,1,0},{0,1,1}};
    auto a = solution.orangesRotting(grid);
    cout << 1;
    return 0;
}






