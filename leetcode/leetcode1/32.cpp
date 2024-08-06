#include<iostream>
#include<vector>
#include<stack>
#include<functional>
#include<algorithm>

using namespace std;

class Solution {
public:
    int longestValidParentheses(string s) {
        vector<int> result;
        int flag=0;
        int n=s.length();
        for(int i=0;i<s.length();i++){
            if(s[i]=='(' && s[i+1]==')'){
                result.push_back(2);
                i++;
                n--;
            }
            else if(s[i]=='('){
                result.push_back(-2);
            }
            else if(s[i]==')'){
                result.push_back(-1);
            }
        }
        while(1){
            flag=0;
            for(int i=0;i<n;i++){
                if(result[i]>0){
                    if(i>0 && i<n-1 && result[i-1]==-2 && result[i+1]==-1){
                        flag=1;
                        result[i]+=2;
                        result.erase(result.begin()+i+1);
                        result.erase(result.begin()+i-1);
                        n-=2;
                        i-=2;
                    }
                    else if(i>1 && result[i-1]>0){
                        flag=1;
                        result[i-1]+=result[i];
                        result.erase(result.begin()+i);
                        n-=1;
                        i-=1;
                    }
                    else if(i<n-1 && result[i+1]>0){
                        flag=1;
                        result[i]+=result[i+1];
                        result.erase(result.begin()+i+1);
                        n-=1;
                        i-=1;
                    }
                }
            }
            if(!flag) break;
        }
        int max=0;
        for(int i:result){
            if(i>max) max=i;
        }
        return max;
    }
};

int main() {
    Solution x;
    string s="(()())";
    int a = x.longestValidParentheses(s);
    cout << a;
    return 0;
}
