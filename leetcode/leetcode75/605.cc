#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool canPlaceFlowers(vector<int>& flowerbed, int n) {
        for(int i=0;i<flowerbed.size();i++){
            if(flowerbed[i]==1) continue;
            if(i==0){
                if(i+1<flowerbed.size()) {
                    if(flowerbed[i+1]==0){
                        flowerbed[i]=1;
                        n--;
                    }
                }
                else n--;
            }
            else if(i==flowerbed.size()-1){
                if(flowerbed[i-1]==0) {
                    flowerbed[i]=1;
                    n--;
                }
            }
            else{
                if(flowerbed[i-1]==0 && flowerbed[i+1]==0) {
                    flowerbed[i]=1;
                    n--;
                }
            }
            if(n<=0) return true;
        }
        if(n<=0) return true;
        else return false;
    }
};


int main() {
    Solution s;
    vector<int> flowerbed={0,1,0};
    bool a = s.canPlaceFlowers(flowerbed, 1) ;
    cout << 1;
    return 0;
}
