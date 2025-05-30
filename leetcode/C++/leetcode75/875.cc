#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int mink=*min_element(piles.begin(),piles.end());
        int maxk=*max_element(piles.begin(),piles.end());
        int hperp = floor((double)h/piles.size());
        mink = ceil((double)mink/hperp);
        maxk = ceil((double)maxk/hperp);

        static function<bool(int)> can_eat = [&](int k){
            int time=0;
            for(auto &p : piles){
                time += ceil((double)p/k);
            }
            return (time <= h);
        };

        while(mink < maxk){
            int half=mink+(maxk-mink)/2;
            
            if(can_eat(half)) maxk=half;
            else mink=half+1;
        }
        return mink;
    }
};

int main() {
    Solution s;
    vector<int> piles = {1000000000,1000000000};
    auto a = s.minEatingSpeed(piles, 3) ;
    cout << a;
    return 0;
}
