#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<string>> result;
    vector<vector<string>> solveNQueens(int n) {
        vector<bool> col(n, true);
        vector<bool> row(n, true);
        vector<bool> left(2*n-1, true);
        vector<bool> right(2*n-1, true);
        vector<vector<bool>> arr={col,row,left,right};
        vector<int> res(2*n,-1);
        fun(arr, res, 0, n);
        return result;
    }
    // int fun(vector<string> arr, int idx, int num, int n){
    //     if(n==num){
    //         result.push_back(arr);
    //         return 0;
    //     } 
    //     for(int i=idx; i<n; i++){
    //         for(int j=0; j<n; j++){
    //             if(arr[i][j]=='x'){
    //                 vector<string> arr2=arr;
    //                 arr2[i][j]='Q';
    //                 for(int x=0;x<n;x++){
    //                     if(arr2[x][j]=='x') arr2[x][j]='.';
    //                     if(arr2[i][x]=='x') arr2[i][x]='.';
    //                 } 
                    
    //                 for(int x=1-n; x<n; x++){
    //                     if(i+x<0 || i+x>=n || j+x<0 || j+x>=n) continue;
    //                     if(arr2[i+x][j+x]=='x') arr2[i+x][j+x]='.';
    //                 }
    //                 for(int x=1-n; x<n; x++){
    //                     if(i-x<0 || i-x>=n || j+x<0 || j+x>=n) continue;
    //                     if(arr2[i-x][j+x]=='x') arr2[i-x][j+x]='.';
    //                 }
    //                 fun(arr2, i, num+1, n);
    //             }
    //         }
    //     }
    //     return 0;
    // }

    int fun(vector<vector<bool>> arr, vector<int> res, int num, int n){
        if(n==num){
            vector<string> T(n,string(n,'.'));
            for(int i=0; i<n; i++){
                T[res[i]][res[n+i]]='Q';
            }
            result.push_back(T);
            return 0;
        } 
        int x=num;
        for(int y=0; y<n; y++){
            if(arr[0][x]&&arr[1][y]&&arr[2][x+y]&&arr[3][n-1+x-y]){
                vector<vector<bool>> arr2=arr; 
                vector<int> res2=res; 
                arr2[0][x]=false;
                arr2[1][y]=false;
                arr2[2][x+y]=false;
                arr2[3][n-1+x-y]=false;

                res2[num]=x;
                res2[n+num]=y;

                fun(arr2, res2, num+1, n);
            }
        }
        
        return 0;
    }
};



int main() {
    Solution s;
    int n=9;
    vector<vector<string>> a = s.solveNQueens(n) ;
    cout << 2;
    return 0;
}
