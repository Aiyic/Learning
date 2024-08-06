#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<vector<int>> results;
        intervals.push_back(newInterval);
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
    
    vector<vector<int>> insert2(vector<vector<int>>& intervals, vector<int>& newInterval) {
        int n=intervals.size();
        if(n==0) return {newInterval};
        int i=0;
        while(i<n && intervals[i][1]<newInterval[0]) i++;
        if(i>=n) intervals.push_back(newInterval);
        else if(newInterval[1]<intervals[i][0]) {
            intervals.insert(intervals.begin()+i,newInterval);
        }
        else{  
            intervals[i][0]=min(intervals[i][0],newInterval[0]);
            if(newInterval[1]>intervals[i][1]){
                intervals[i][1]=newInterval[1];
                int j=i+1;
                while(j<intervals.size() && intervals[i][1]>=intervals[j][0]) {
                    intervals[i][1]=max(intervals[i][1],intervals[j][1]);
                    j++;
                }
                if(j>i+1) intervals.erase(intervals.begin()+i+1,intervals.begin()+j);
            }
        }
        return intervals;
    }
};


int main() {
    Solution s;
    vector<vector<int>> intervals = {{1,5}};
    vector<int> newInterval = {6,8};
    vector<vector<int>> a = s.insert2(intervals,newInterval) ;
    cout << 2;
    return 0;
}
