
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int countTriples(int n) {
        if(n<5) return 0;
        vector<int> q;
        q.resize(n+1);
        for(int i=3;i<=n;i++){
            q[i]=i*i;
        }
        int res=0;
        for(int i=3;i<n;i++){
            for(int j=i+1;j<n;j++){
                auto x = equal_range(q.begin()+j,q.end(),q[i]+q[j]);
                if(x.first!=x.second)  
                    res+=2;
            }
        }
        return res;
    }
};

int main() {
    Solution s;


    auto a = s.countTriples(10) ;
    cout << a;
    return 0;
}
