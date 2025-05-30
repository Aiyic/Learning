#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        static auto num = [&](int idx){
            if(idx==-1 || idx==nums.size()) return INT_MIN;
            else return nums[idx];
        };

        static function<int(int,int)> fun = [&](int left, int right){
            if(left==right) return left;
            int half = left+(right-left)/2;
            if(num(half)>=num(half-1) && num(half)>=num(half+1)){
                return half;
            }
            else{
                if(num(half)>num(half+1))
                    return fun(left,half);
                else 
                    return fun(half+1,right);
            }
            return -1;
        };

        return fun(0,nums.size()-1);
    }
};

int main() {
    Solution s;
    vector<int> nums = {-2147483648,-2147483647};
    auto a = s.findPeakElement(nums) ;
    cout << 1;
    return 0;
}
