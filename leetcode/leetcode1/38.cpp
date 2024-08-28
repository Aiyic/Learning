#include<iostream>
#include<vector>
#include<stack>
#include<functional>
#include<algorithm>

using namespace std;

class Solution {
public:
    string countAndSay(int n) {
        if(n==1) return string("1");
        string str=countAndSay(n-1);
        string result="";
        while(str.length()){
            int i=1;
            while(str[i]==str[0]) i++;
            result=result+(char)(i+'0')+str[0];
            str=string(str.begin()+i,str.end());
        }
        return result;
    }
};

int main() {
    Solution x;
    string a=x.countAndSay(4);
    cout << 1;
    return 0;
}
