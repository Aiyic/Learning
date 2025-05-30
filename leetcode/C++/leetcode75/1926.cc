#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int nearestExit(vector<vector<char>>& maze, vector<int>& entrance) {
        queue<pair<int,int>> location;
        set<pair<int,int>> passed;
        const pair<int,int> start = {entrance[0],entrance[1]};
        location.emplace(start);
        const int m=maze.size(),n=maze[0].size();

        int res=-1; // 走过路径长度
        while(!location.empty()){
            res++;
            int locationsize=location.size(); // 广度遍历节点集合
            while(locationsize--){
                auto t = location.front();
                location.pop();

                auto fd = passed.find(t);
                if(fd != passed.end()) continue; // 节点已访问

                if(t!=start && (t.first<=0 || t.first>=m-1 || t.second<=0 || t.second>=n-1)) return res; // 终点
                passed.emplace(t); // 标记已访问

                if(t.first>0 && maze[t.first-1][t.second]=='.') location.emplace(t.first-1,t.second);
                if(t.first<m-1 && maze[t.first+1][t.second]=='.') location.emplace(t.first+1,t.second);
                if(t.second>0 && maze[t.first][t.second-1]=='.') location.emplace(t.first,t.second-1);
                if(t.second<n-1 && maze[t.first][t.second+1]=='.') location.emplace(t.first,t.second+1);
            }
        }
        return -1;
    }
};





int main() {
    Solution solution;
    vector<vector<char>> maze={{'+','+','+'},{'.','.','.'},{'+','+','+'}};
    vector<int> entrance={1,0};
    auto a = solution.nearestExit(maze, entrance);
    cout << 1;
    return 0;
}






