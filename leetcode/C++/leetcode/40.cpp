#include<iostream>
#include<vector>
#include<stack>
#include<functional>
#include<algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<vector<int>> result;
        vector<int> vec;
        sort(candidates.begin(),candidates.end());
        int n = candidates.size();
        fun(result, candidates, vec, n-1, target);
        return result;
    }
    int fun(vector<vector<int>>& result, vector<int>& candidates, vector<int> vec, int idx, int target){
        if(idx<0) return 0;
        if(target == candidates[idx]){
            int idxx=idx-1;
            while(idxx>=0 && candidates[idx] == candidates[idxx]) idxx--;
            fun(result, candidates, vec, idxx, target);
            vec.push_back(candidates[idx]);
            result.push_back(vec);
        }
        else if(target < candidates[idx])
            fun(result, candidates, vec, idx-1, target);
        else if(target > candidates[idx]){
            int idxx=idx-1;
            while(idxx>=0 && candidates[idx] == candidates[idxx]) idxx--;
            fun(result, candidates, vec, idxx, target);
            vec.push_back(candidates[idx]);
            fun(result, candidates, vec, idx-1, target-candidates[idx]);
        }
        return 0;
    }
};

int main() {
    Solution x;
    vector<int> candidates = {1,1,1,3,3,5};
    int target = 8;
    vector<vector<int>> a = x.combinationSum2(candidates, target) ;
    cout << 1;
    return 0;
}
