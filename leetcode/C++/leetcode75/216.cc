
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<vector<int>> res;
        vector<int> used(9); 

        static function<void(int)> fun = [&](int deepth){
            if(deepth==0) {
                vector<int> x;
                int sum=0;
                for(int i=1;i<=9;++i){
                    if(used[i]==1) {
                        x.push_back(i);
                        sum+=i;
                    }
                }
                if(sum==n) res.push_back(move(x));
                return;
            }
            for(int i=1;i<=9;++i){
                if(used[i]==1) return;
                used[i]=1;
                fun(deepth-1);
                used[i]=0;
            }
        };

        fun(k);
        return res;
    }
};

int main() {
    Solution s;
    auto a = s.combinationSum3(4, 1) ;
    cout << 1;
    return 0;
}
