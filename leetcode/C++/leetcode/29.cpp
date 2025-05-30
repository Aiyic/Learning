#include<iostream>

using namespace std;

class Solution {
public:
    int divide(int dividend, int divisor) {
        int bias=0;
        if(dividend==INT_MIN) {
            if(divisor > 0) {dividend+=divisor; bias=-1;}
            else if(divisor == INT_MIN) return 1;
            else if(divisor == -1) return INT_MAX;
            else {dividend-=divisor; bias=1; }
        }else{
            if(divisor == INT_MIN) return 0;
        }

        int result = 0;
        int flag = 1;
        if(dividend < 0){
            flag*=-1;
            dividend = -dividend;
        } 
        if(divisor < 0){
            flag*=-1;
            divisor = -divisor;
        }

        for(int i=0; i<31; i++){
            if((divisor << i)>dividend ) break;
            if((divisor << i)>(divisor << 1+i)
                || ((divisor << i)<=dividend 
                    && (divisor << 1+i)>dividend ) 
                || i>=29){
                result += (1 << i);
                dividend -= (divisor << i);
                i=-1;
            }
        }
        return flag*result+bias;
    }
};

int main() {
    Solution x;
    int a = x.divide(1100540749,-1090366779);
    return 0;
}
