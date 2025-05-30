#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int x=matrix.size();
        int y=matrix[0].size();

        vector<bool> r(x,false);
        vector<bool> c(y,false);
        for(int i=0;i<x;i++){
            for(int j=0;j<y;j++){
                if(!matrix[i][j]){
                    r[i]=true;
                    c[j]=true;
                }
            }
        }
        for(int i=0;i<x;i++){
            for(int j=0;j<y;j++){
                if(r[i] || c[j])
                    matrix[i][j]=0;
            }
        }
    }
};


int main() {
    Solution solution;
    vector<vector<int>> matrix = {{0,1,2,0},{3,4,5,2},{1,3,1,5}};
    solution.setZeroes(matrix) ;
    cout << 1;
    return 0;
}