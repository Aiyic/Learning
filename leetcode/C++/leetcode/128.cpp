#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> s(nums.begin(),nums.end());
        int maxn=0;
        for(int x : s){
            int n=1;
            int i=1;
            if(s.find(x-1)!=s.end()) continue;
            while(s.find(x+i++)!=s.end()) n++;
            maxn = max(maxn,n);
        }
        return maxn;
    }
};

int main() {
    Solution solution;
    vector<int> nums  = {100,4,200,1,3,2};
    int a = solution.longestConsecutive(nums ) ;
    cout << 1;
    return 0;
}