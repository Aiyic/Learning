#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        vector<int> res(asteroids.size());
        res[0]=asteroids[0];
        int i=0,j=1;
        while(j<asteroids.size()){
            if(i<0) res[++i]=asteroids[j++];
            else if(res[i]>0 && asteroids[j]<0){
                if(res[i]+asteroids[j]>0) j++;
                else if(res[i]+asteroids[j]<0) i--;
                else {
                    i--;j++;
                }
            }
            else res[++i]=asteroids[j++];
        }
        res.erase(res.begin()+i+1,res.end());
        return res;
    }
};

int main() {
    Solution s;
    vector<int> asteroids={1,-2,-2,-2};
    vector<int> a=s.asteroidCollision(asteroids) ;
    cout << 1;
    return 0;
}
