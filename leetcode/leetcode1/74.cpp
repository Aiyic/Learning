#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int step=matrix[0].size();
        int l=0,r=matrix.size()*step-1;
        while(l<=r){
            int mid=l+(r-l)/2;
            if(matrix[mid/step][mid%step]==target) return true;
            else if(matrix[mid/step][mid%step]<target) l=mid+1;
            else if(matrix[mid/step][mid%step]>target) r=mid-1;
        }
        return false;
    }
};


int main() {
    Solution solution;
    vector<vector<int>> matrix = {{1}};
    bool a = solution.searchMatrix(matrix, 13) ;
    cout << a;
    return 0;
}