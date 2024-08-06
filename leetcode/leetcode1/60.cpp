#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    string nums="123456789";
    string getPermutation(int n, int k) {
        if(n==1 && k==1) return "1";
        else return fun("",n,k-1);
    }
    string fun(string str, int n, int k){
        if(n<=1) return str+nums[0];
        int i=1,j=i;

        while(i<n) j=j*i++;

        str += nums[k/j];
        nums.erase(nums.begin()+k/j);
        return fun(str,n-1,k%j);
    }
};


int main() {
    Solution s;
    string a = s.getPermutation(3,2) ;
    cout << a;
    return 0;
}

/*

1-2-6-24

k=23/6=3
k=7/6=1
k=6/6=1


1234
1243
1324
1342
1423
1432

2134
2143
2314
2341
2413
2431

3124
3142




1-2-6

134
143
314
341
413
431



1

14
41



*/
