#include<iostream>
#include<vector>
#include<stack>
#include<functional>
#include<algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> result;
        vector<int> vec;
        int n = candidates.size();
        fun(result, candidates, vec, n-1, target);
        return result;
    }
    int fun(vector<vector<int>>& result, vector<int>& candidates, vector<int> vec, int idx, int target){
        if(idx<0) return 0;
        if(target == candidates[idx]){
            fun(result, candidates, vec, idx-1, target);
            vec.push_back(candidates[idx]);
            result.push_back(vec);
            return 0;
        }
        else if(target < candidates[idx]){
            fun(result, candidates, vec, idx-1, target);
            return 0;
        }
        else if(target > candidates[idx]){
            fun(result, candidates, vec, idx-1, target);
            vec.push_back(candidates[idx]);
            fun(result, candidates, vec, idx, target-candidates[idx]);
            return 0;
        }
        return 0;
    }
};

int main() {
    Solution x;
    vector<int> candidates = {2,3,5};
    int target = 8;
    vector<vector<int>> a = x.combinationSum(candidates, target) ;
    cout << 1;
    return 0;
}
