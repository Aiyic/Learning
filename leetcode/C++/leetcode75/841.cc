#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool canVisitAllRooms(vector<vector<int>>& rooms) {
        unordered_set<int> keys;
        dfs(rooms,keys,0);
        return keys.size()==rooms.size();;
    }

    void dfs(vector<vector<int>>& rooms, unordered_set<int> & keys, int cur){
        if(keys.count(cur)) return;
        keys.insert(cur);
        for(int & subkey : rooms[cur]){
            dfs(rooms,keys,subkey);
        }
    }


    bool canVisitAllRooms2(vector<vector<int>>& rooms) {
        vector<bool> has_inter;
        has_inter.resize(rooms.size());

        queue<int> has_keys;
        has_keys.push(0);
        while(!has_keys.empty()){
            int key = has_keys.front();
            has_keys.pop();
            if(has_inter[key]==true) continue;
            else{
                has_inter[key]=true;
                for(auto & subkey : rooms[key]){
                    if(has_inter[subkey]==false) has_keys.push(subkey);
                }
            }
        }
        for(auto x : has_inter){
            if(!x) return false;
        }
        return true;
    }
};


int main() {
    Solution s;
    vector<vector<int>> rooms={{1},{2},{3},{}};
    auto a = s.canVisitAllRooms(rooms) ;
    cout << 1;
    return 0;
}
