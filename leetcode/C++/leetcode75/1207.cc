#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool uniqueOccurrences(vector<int>& arr) {
        unordered_map<int,int> arrmap;
        for(auto &x : arr){
            if(arrmap.count(x)) arrmap[x]++;
            else arrmap[x]=1;
        }
        unordered_set<int> arrset;
        for(auto &x : arrmap){
            if(arrset.count(x.second)) return false;
            else arrset.insert(x.second);
        }
        return true;
    }
};

int main() {
    Solution s;
    vector<int> nums1={1,2,3,4};
    vector<int> nums2={1,2,3,4};
    bool a = s.uniqueOccurrences(nums1) ;
    cout << 1;
    return 0;
}
