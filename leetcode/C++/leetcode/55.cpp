#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool canJump(vector<int>& nums) {
        for(int i=0;i<nums.size()-1;i++){
            if(nums[i]==0){
                bool flag=false;
                for(int j=i;j>=0;j--) {
                    if(nums[j]>i-j) {
                        flag=true;
                        break;
                    }
                }
                if(flag) continue;
                else return false;
            }
        }
        return true;
    }
};


int main() {
    Solution s;
    vector<int> nums={3,2,1,0};
    bool a = s.canJump(nums) ;
    cout << 2;
    return 0;
}
