#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        vector<int> citys(isConnected.size());
        int res=0;
        for(int x=0; x<citys.size(); ++x){
            if(citys[x]==0){
                dfs(isConnected,citys,x);
                res++;
            }
        }
        return res;
    }

    void dfs(vector<vector<int>>& isConnected, vector<int> &citys, int node){
        if(citys[node]) return;

        citys[node]=1;
        for(int x=0; x<citys.size(); ++x){
            if(isConnected[node][x]==1 && citys[x]==0){
                dfs(isConnected,citys,x);
            }
        }
    }
};

int main() {
    Solution s;
    vector<vector<int>> nums={{1,0,0,1},{0,1,1,0},{0,1,1,1},{1,0,1,1}};

    auto a = s.findCircleNum(nums) ;
    cout << 1;
    return 0;
}
