#include<iostream>
#include<vector>
#include<ranges>
#include<algorithm>

using namespace std;

class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        struct cmp
        {
            inline bool operator()(const vector<int>& a, const vector<int>& b){
                if(a.at(0)==b.at(0)) return a.at(1)<b.at(1);
                else return a.at(0)<b.at(0);
            }
        };
        sort(intervals.begin(),intervals.end(),cmp());
        int delnum=0;
        int i=0,j=1;
        while(j<intervals.size()){
            if(intervals[i][0]==intervals[j][0]){
                ++delnum;
                ++j;
                continue;
            }
            else{
                if(intervals[i][1]>intervals[j][0]){
                    if(intervals[i][1]<intervals[j][1]){
                        ++delnum;
                        ++j;
                        continue;
                    }
                    else{
                        ++delnum;
                    }
                }
            }
            i=j;
            ++j;
        }

        return delnum;
    }
};


int main() {
    Solution s;
    vector<vector<int>> intervals={{1,2},{2,3},{3,4},{1,3}};
    auto a = s.eraseOverlapIntervals(intervals);
    cout << a;
    return 0;
}
