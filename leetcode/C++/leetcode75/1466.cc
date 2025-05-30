#include<bits/stdc++.h>
using namespace std;

struct cmp
{
    bool operator()(const vector<int>& a, const vector<int>& b){
        return (min(a[0],a[1]) < min(b[0],b[1]));
    }
};

class Solution {
public:

    int minReorder(int n, vector<vector<int>> &connections) {
        vector<pair<int, int>> e[n]; // 邻接矩阵
        for (auto &it: connections) {
            e[it[0]].emplace_back(it[1], 1);
            e[it[1]].emplace_back(it[0], 0);
        }
        function<int(int, int)> dfs = [&](int cur, int pre) {
            int res = 0;
            for (auto [j, w]: e[cur])
                if (j != pre) // 深度遍历, 不存在环路的判断条件
                    res += w + dfs(j, cur);
            return res;
        };
        return dfs(0, -1);
    }

    // int minReorder(int n, vector<vector<int>>& connections) {
    //     // deque<vector<int>> lines(connections.begin(),connections.end());
    //     sort(connections.begin(),connections.end(),cmp());
    //     auto & lines = connections;
    //     unordered_set<int> s(n);
    //     int csize = connections.size();
    //     s.insert(0);
    //     int res=0;
    //     for(int i=0; i<csize; ++i){
    //         if(s.find(lines[i][0]) != s.end()){
    //             s.insert(lines[i][1]);
    //             ++res; 
    //         }
    //         else if(s.find(lines[i][1]) != s.end()){
    //             s.insert(lines[i][0]);
    //         }
    //         else{
    //             lines.emplace_back(lines[i]);
    //             csize++;
    //         }
    //     }
    //     return res;
    // }
};




int main() {
    Solution solution;
    vector<vector<int>> connections = {{0,1},{1,3},{2,3},{4,0},{4,5}};
    auto a = solution.minReorder(6,connections) ;
    cout << a;
    return 0;
}






