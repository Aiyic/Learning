#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int result;
    int totalNQueens(int n) {
        vector<bool> col(n, true);
        vector<bool> row(n, true);
        vector<bool> left(2*n-1, true);
        vector<bool> right(2*n-1, true);
        vector<vector<bool>> arr={col,row,left,right};
        fun(arr, 0, n);
        return result;
    }
    int fun(vector<vector<bool>> arr, int num, int n){
        if(n==num){
            result++;
            return 0;
        } 
        int x=num;
        for(int y=0; y<n; y++){
            if(arr[0][x]&&arr[1][y]&&arr[2][x+y]&&arr[3][n-1+x-y]){
                vector<vector<bool>> arr2=arr; 
                arr2[0][x]=false;
                arr2[1][y]=false;
                arr2[2][x+y]=false;
                arr2[3][n-1+x-y]=false;
                fun(arr2, num+1, n);
            }
        }
        return 0;
    }
};



int main() {
    Solution s;
    int n=9;
    int a = s.totalNQueens(n) ;
    cout << 2;
    return 0;
}
