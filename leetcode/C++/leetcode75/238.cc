#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        unordered_map<int,int> nums_map={};
        vector<int> results;
        for(int &x : nums){
            if(nums_map.find(x)==nums_map.end()) nums_map[x]=1;
            else nums_map[x]*=x;
        }
        for(int &x : nums){
            int res=1;
            for(auto &y : nums_map){
                if(x==y.first) res*=y.second;
                else res=res*y.first*y.second;
            }
            results.push_back(res);
        }
        return results;
    }
};

int main() {
    Solution s;
    vector<int> nums={1,2,3,4};
    vector<int> a = s.productExceptSelf(nums) ;
    cout << 1;
    return 0;
}
