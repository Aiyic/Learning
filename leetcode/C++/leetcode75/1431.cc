#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<bool> kidsWithCandies(vector<int>& candies, int extraCandies) {
        int maxv = *max_element(candies.begin(),candies.end());
        vector<bool> res;
        maxv-=extraCandies;
        for(int& i : candies){
            if(i>=maxv) res.push_back(true);
            else res.push_back(false);
        }
        return res;
    }
};


int main() {
    Solution s;
    vector<int> candies={2,3,5,1,3};
    vector<bool> a = s.kidsWithCandies(candies,3) ;
    cout << 1;
    return 0;
}
