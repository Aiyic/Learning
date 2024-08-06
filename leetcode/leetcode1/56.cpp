#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        vector<vector<int>> results;
        sort(intervals.begin(),intervals.end());
        for(int i=0;i<intervals.size();i++){
            int left=intervals[i][0],right=intervals[i][1];
            for(int j=i+1;j<intervals.size();j++){
                if(intervals[j][0]<=right){
                    if(intervals[j][1]>=right) {
                        right=intervals[j][1];
                    }
                    i++;
                }
                else{
                    break;
                }
            }
            results.push_back({left,right});
        }
        return results;
    }
};


int main() {
    Solution s;
    vector<vector<int>> intervals = {{1,4},{0,4}};
    vector<vector<int>> a = s.merge(intervals) ;
    cout << 2;
    return 0;
}
