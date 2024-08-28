#include<iostream>
#include<vector>
#include<stack>
#include<functional>
#include<algorithm>

using namespace std;

class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        /*
        
        (0,2) -> (2,(4-1)-0)
                 (2,3)
        (i,j) -> (j,(n-1)-i)
        (0,0) -> (0,2)
        
        (1,0) -> (0,2)
        ((n-1)-j,i) -> (i,j)

        1 2      3 1
        3 4  ->  4 2

        */

        int n=matrix.size();
        for(int idx=0; idx<(n-1)/2+(n-1)%2; idx++){
            for(int idy=idx; idy<n-1-idx; idy++){
                int x,y;
                int newx,newy;
                x=idx;
                y=idy;
                int num0=matrix[x][y];
                for(int i=1;i<4;i++){
                    newx=(n-1)-y,newy=x;
                    matrix[x][y]=matrix[newx][newy];
                    x=newx;
                    y=newy;
                }
                matrix[idy][n-1-idx]=num0;
            }
        }
    }
};

int main() {
    Solution x;
    vector<int> l1={1,2,3,4,4};
    vector<int> l2={1,6,7,4,4};
    vector<int> l3={1,8,9,4,4};
    vector<int> l4={1,2,3,4,4};
    vector<int> l5={1,2,3,4,4};
    vector<vector<int>> nums={l1,l2,l3,l4,l5};
    x.rotate(nums) ;
    cout << 1;
    return 0;
}
