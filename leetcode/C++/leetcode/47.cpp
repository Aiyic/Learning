#include<iostream>
#include<vector>
#include<stack>
#include<functional>
#include<algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        if(nums.size()==1){
            return vector<vector<int>>(1,(vector<int>(1,nums[0])));
        }
        vector<vector<int>> result;
        sort(nums.begin(),nums.end());
        int last=INT_MAX;
        for(int i=0;i<nums.size();i++){
            if(nums[i]==last) continue;
            last=nums[i];
            vector<int> nums2=nums;
            nums2.erase(nums2.begin()+i);
            vector<vector<int>> result2 = permuteUnique(nums2);
            for(auto &x:result2){
                x.push_back(nums[i]);
            }
            result.insert(result.end(),result2.begin(),result2.end());
        }
        return result;
    }
};

int main() {
    Solution x;
    vector<int> nums={1,1,3};
    vector<vector<int>> a = x.permuteUnique(nums) ;
    cout << 1;
    return 0;
}
