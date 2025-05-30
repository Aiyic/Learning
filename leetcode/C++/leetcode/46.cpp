#include<iostream>
#include<vector>
#include<stack>
#include<functional>
#include<algorithm>

using namespace std;

/*
result=[]
for(i : ixyz)
    nums[i]+fun(nums[]-i)
    nums[i]+[[xxx][yyy][zzz]]
    [[ixxx][iyyy][izzz]]
    result + [[ixxx][iyyy][izzz]]
return result
*/

class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        if(nums.size()==1){
            return vector<vector<int>>(1,(vector<int>(1,nums[0])));
        }
        vector<vector<int>> result;
        for(int i=0;i<nums.size();i++){
            vector<int> nums2=nums;
            nums2.erase(nums2.begin()+i);
            vector<vector<int>> result2 = permute(nums2);
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
    vector<int> nums={1,2,3};
    vector<vector<int>> a = x.permute(nums) ;
    cout << 1;
    return 0;
}
