#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

class Solution {
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        struct cmp {
            inline bool operator()(const vector<int>& a, const vector<int>& b){
                if(a.at(0)<b.at(0)) return true;
                else if(a.at(0)==b.at(0)) return a.at(1)<b.at(1);
                else return false;
            }
        };
        
        stable_sort(points.begin(),points.end(),cmp());
        int biubiu=0;
        int i=0,j=1;

        while(i<points.size()){
            int left=points[i][0];
            int right=points[i][1];
            j=i+1;
            while(j<points.size()){
                left=max(left,points[j][0]);
                right=min(right,points[j][1]);
                if(left<=right) {
                    ++j;
                    continue;
                }
                else {
                    break;
                }
            }
            biubiu++;
            i=j;
        }

        return biubiu;
    }
};


int main() {
    Solution s;
    // vector<vector<int>> points={{10,16},{2,8},{1,6},{7,12}};
    vector<vector<int>> points={{1,2},{2,3},{3,4},{4,5}};
    auto a = s.findMinArrowShots(points);
    cout << a;
    return 0;
}
