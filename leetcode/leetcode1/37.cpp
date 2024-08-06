#include<iostream>
#include<vector>
#include<stack>
#include<functional>
#include<algorithm>

using namespace std;

class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {
        vector<int> x,y,value;
        int n=0;
        for(int i=0;i<9;i++){
            for(int j=0;j<9;j++){
                if(board[i][j]=='.'){
                    x.push_back(i);
                    y.push_back(j);
                    n++;
                }
            }
        }
        for(int k=0;k<n;k++){
            for(int v=1;v<10;v++){
                if(board[x[k]][y[k]]!='.') v=board[x[k]][y[k]]-'0'+1;
                board[x[k]][y[k]]='0'+v;
                if(board[x[k]][y[k]]>'9'){
                    board[x[k]][y[k]]='.';
                    break;
                }
                if(isValidSudoku(board, x[k], y[k])) break;
                else{
                    board[x[k]][y[k]]='.';
                    continue;
                }
            }
            if(board[x[k]][y[k]]=='.') k-=2;
        }
    }
    bool isValidSudoku(vector<vector<char>>& board,int x,int y) {
        int p[10]={0},q[10]={0},r[10]={0};
        for(int i=0;i<9;i++){
            if(board[x][i]=='.') continue;
            else{
                int idx=board[x][i]-'0';
                if(p[idx]==0) p[idx]=1;
                else return false;
            } 
        }
        for(int i=0;i<9;i++){
            if(board[i][y]=='.') continue;
            else{
                int idx=board[i][y]-'0';
                if(q[idx]==0) q[idx]=1;
                else return false;
            } 
        }
        int i=x/3;
        int j=y/3;
        for(int x=0;x<3;x++){
            for(int y=0;y<3;y++){
                if(board[x+3*i][y+3*j]=='.') continue;
                else{
                    int idx=board[x+3*i][y+3*j]-'0';
                    if(r[idx]==0) r[idx]=1;
                    else return false;
                } 
            }
        } 
        return true;
    }
};

int main() {
    Solution x;
    vector<vector<char>> board = 
    {{'5','3','.','.','7','.','.','.','.'}
    ,{'6','.','.','1','9','5','.','.','.'}
    ,{'.','9','8','.','.','.','.','6','.'}
    ,{'8','.','.','.','6','.','.','.','3'}
    ,{'4','.','.','8','.','3','.','.','1'}
    ,{'7','.','.','.','2','.','.','.','6'}
    ,{'.','6','.','.','.','.','2','8','.'}
    ,{'.','.','.','4','1','9','.','.','5'}
    ,{'.','.','.','.','8','.','.','7','9'}};


    x.solveSudoku(board);
    cout << 1;
    return 0;
}
