#include<iostream>
#include<vector>
#include<stack>
#include<functional>
#include<algorithm>

using namespace std;

class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        for(int i=0;i<9;i++){
            int result[10]={0};
            for(int j=0;j<9;j++){
                if(board[i][j]=='.') continue;
                else{
                    int idx=board[i][j]-'0';
                    if(result[idx]==0) result[idx]=1;
                    else return false;
                } 
            }
        }
        for(int i=0;i<9;i++){
            int result[10]={0};
            for(int j=0;j<9;j++){
                if(board[j][i]=='.') continue;
                else{
                    int idx=board[j][i]-'0';
                    if(result[idx]==0) result[idx]=1;
                    else return false;
                } 
            }
        }
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                int result[10]={0};
                for(int x=0;x<3;x++){
                    for(int y=0;y<3;y++){
                        if(board[x+3*i][y+3*j]=='.') continue;
                        else{
                            int idx=board[x+3*i][y+3*j]-'0';
                            if(result[idx]==0) result[idx]=1;
                            else return false;
                        } 
                    }
                }
            }
        }
        return true;
    }
};

int main() {
    Solution x;
    vector<vector<char>> board = 
    {{'8','3','.','.','7','.','.','.','.'}
    ,{'6','.','.','1','9','5','.','.','.'}
    ,{'.','9','8','.','.','.','.','6','.'}
    ,{'8','.','.','.','6','.','.','.','3'}
    ,{'4','.','.','8','.','3','.','.','1'}
    ,{'7','.','.','.','2','.','.','.','6'}
    ,{'.','6','.','.','.','.','2','8','.'}
    ,{'.','.','.','4','1','9','.','.','5'}
    ,{'.','.','.','.','8','.','.','7','9'}};


    bool a = x.isValidSudoku(board);
    cout << 1;
    return 0;
}
