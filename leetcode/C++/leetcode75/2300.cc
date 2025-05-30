#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> successfulPairs(vector<int>& spells, vector<int>& potions, long long success) {
        vector<int> res;
        sort(potions.begin(),potions.end());
        for(auto & x : spells){
            double yy=static_cast<double>(success)/x;
            auto f = lower_bound(potions.begin(),potions.end(),yy);
            int num = distance(f,potions.end());
            res.push_back(num);
        }
        return res;
    }
};

int main() {
    Solution s;
    vector<int> spells = {5,5,5};
    vector<int> potions = {1,2,3,4,5};
    auto a = s.successfulPairs(spells,potions,7) ;
    cout << 1;
    return 0;
}
