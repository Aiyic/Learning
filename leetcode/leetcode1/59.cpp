#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        int left=0,right=n;
        int top=0,bottom=n;
        int loop=0,x=1;
        n=n*n;
        vector<vector<int>> matrix(bottom, vector<int>(right));
        while(x<=n){
            loop++;
            if(loop%4==1){
                for(int i=left;i<right;i++){
                    matrix[top][i]=x++;
                }
                top++;
            }
            else if(loop%4==2){
                for(int i=top;i<bottom;i++){
                    matrix[i][right-1]=x++;
                }
                right--;
            }
            else if(loop%4==3){
                for(int i=right-1;i>=left;i--){
                    matrix[bottom-1][i]=x++;
                }
                bottom--;
            }
            else{
                for(int i=bottom-1;i>=top;i--){
                    matrix[i][left]=x++;
                }
                left++;
            }
        }
        return matrix;
    }
};


int main() {
    Solution s;
    vector<vector<int>> a = s.generateMatrix(3) ;
    cout << 2;
    return 0;
}
