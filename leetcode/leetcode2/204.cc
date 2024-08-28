
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int countPrimes(int n) {
        if(n<=2) return 0;
        vector<int> nums;
        nums.resize(n+1);
        nums[0]=1;
        nums[1]=1;
        int res=0;
        for(int i=2;i<n;i++){ // i is or not
            if(nums[i]==0 && is_zhishu(i)){
                res++;          
                for(int j=2;j*i<=n;j++){
                    nums[j*i]=1;
                }
            }      
        }
        return res;
    }

    bool is_zhishu(int x){
        if(x<2) return false;    
        int i=2;
        while(i*i<=x){
            if(x%i==0) return false;
            else i++;
        }
        return true;
    }
};

int main() {
    Solution s;


    auto a = s.countPrimes(10) ;
    cout << a;
    return 0;
}
