#include<iostream>
#include<vector>
#include<stack>
#include<functional>
#include<algorithm>

using namespace std;

class Solution {
public:
    string multiply(string num1, string num2) {
        if(num1=="0" || num2=="0") return string("0");
        int n1=num1.length(),n2=num2.length();
        int number1[200]={0},number2[200]={0};
        for(int i=0;i<n1;i++){
            number1[i] = num1[n1-1-i]-'0';
        }
        for(int i=0;i<n2;i++){
            number2[i] = num2[n2-1-i]-'0';
        }
        int number[401]={0};
        for(int i=0;i<n1;i++){
            for(int j=0;j<n2;j++){
                number[i+j]+=number1[i]*number2[j];
            }
        }

        for(int i=0;i<n1+n2;i++){
            if(number[i]>=10){
                number[i+1] += number[i]/10;
                number[i] = number[i]%10;
            }
        }
        string result="";
        for(int i=n1+n2-1;i>=0;i--){
            result += (number[i]+'0');
        }
        if(result[0]=='0') return string(result,1,n1+n2-1);
        return result;
    }
};

int main() {
    Solution x;
    string num1="9133",num2="0";
    string a = x.multiply(num1, num2) ;
    cout << 423*456 << ' ' << a;
    return 0;
}
