#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        unordered_map<string, set<pair<string,double>>> e;
        for(int i=0; i<equations.size(); ++i){
            e[equations[i][0]].emplace(equations[i][1], values[i]);
            e[equations[i][0]].emplace(equations[i][0], 1);
            e[equations[i][1]].emplace(equations[i][0], 1/values[i]);
            e[equations[i][1]].emplace(equations[i][1], 1);
        }
        
        function<double(string,string,unordered_set<string>&)> dfs = [&](string src, string dir, unordered_set<string> &searched){
            if(searched.find(src)!=searched.end()) return -1.0;
            searched.insert(src);
            
            for(auto & [node, val] : e[src]){
                if(node==dir) return val;
                else{
                    double v = dfs(node, dir, searched);
                    if(v>0){
                        e[src].emplace(dir, val*v);
                        return val*v;
                    }
                }
            }
            return -1.0;
        };

        vector<double> res;
        for(auto &q : queries){
            unordered_set<string> searched={};
            res.push_back(dfs(q[0],q[1],searched));
        }
        return res;

    }
};




int main() {
    Solution solution;
    vector<vector<string>> equations={{"a","b"},{"b","c"}};
    vector<double> values={2.0,3.0};
    vector<vector<string>> queries={{"a","c"},{"b","a"},{"a","e"},{"a","a"},{"x","x"}};
    auto a = solution.calcEquation(equations,values,queries);
    cout << 1;
    return 0;
}






