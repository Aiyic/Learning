#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> findDifference(vector<int>& nums1, vector<int>& nums2) {
        unordered_set<int> numset1(nums1.begin(),nums1.end());
        unordered_set<int> numset2(nums2.begin(),nums2.end());
        vector<vector<int>> res;
        for(auto &x : numset1){
            if(numset2.find(x)==numset2.end()) res[0].push_back(x);
        }
        for(auto &x : numset2){
            if(numset1.find(x)==numset1.end()) res[1].push_back(x);
        }
        return res;
    }
};

int main() {
    Solution s;
    vector<int> nums1={1,2,3,4};
    vector<int> nums2={1,2,3,4};
    vector<vector<int>> a = s.findDifference(nums1,nums2) ;
    cout << 1;
    return 0;
}
