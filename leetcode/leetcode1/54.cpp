#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int left=0,right=matrix[0].size();
        int top=0,bottom=matrix.size();
        int loop=0;
        int n=right*bottom;
        vector<int> res;
        while(res.size()!=n){
            loop++;
            if(loop%4==1){
                for(int i=left;i<right;i++){
                    res.push_back(matrix[top][i]);
                }
                top++;
            }
            else if(loop%4==2){
                for(int i=top;i<bottom;i++){
                    res.push_back(matrix[i][right-1]);
                }
                right--;
            }
            else if(loop%4==3){
                for(int i=right-1;i>=left;i--){
                    res.push_back(matrix[bottom-1][i]);
                }
                bottom--;
            }
            else{
                for(int i=bottom-1;i>=top;i--){
                    res.push_back(matrix[i][left]);
                }
                left++;
            }
        }
        return res;
    }
};


int main() {
    Solution s;
    vector<vector<int>> matrix={{1,2,3,4},{5,6,7,8},{9,10,11,12}};
    vector<int> a = s.spiralOrder(matrix) ;
    cout << 2;
    return 0;
}
