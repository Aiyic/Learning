#include<iostream>
#include<vector>
#include<stack>
#include<functional>
#include<algorithm>

using namespace std;

class Solution {
public:
    double myPow(double x, int n) {
        if(x==0) return 0;
        if(x==1) return 1;
        if(x==-1) return n%2==0?1:-1;
        if(n==0) return 1;
        if(n==1) return x;
        if(n==-1) return 1/x;
        
        int n2=n/2;
        double result = myPow(x,n2);
        result*=result;
        if(n-n2-n2==1) result*=x;
        else if(n-n2-n2==-1) result/=x;
        return result;
    }
};




int main() {
    Solution s;
    double x=34.00515;
    int n=-3;
    double a = s.myPow(x,n) ;
    cout << 1/x/x/x;
    return 0;
}
