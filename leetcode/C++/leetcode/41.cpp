#include<iostream>
#include<vector>
#include<stack>
#include<functional>
#include<algorithm>

using namespace std;

class Solution {
public:
   int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();
         for(int i=0; i<n; i++){
            if(nums[i]>=1 && nums[i]<=n && i!=nums[i]-1){
                int x=nums[i],y=nums[nums[i]-1];
                swap(nums[i],nums[nums[i]-1]);
                if(x!=y) i--;
            }
        }
        for(int i=0; i<n; i++){
            if(i+1!=nums[i]) return i+1;
        }
        return n+1;
    }

    int firstMissingPositive2(vector<int>& nums) {
        int* record = new int[500000]();
        for(int i : nums){
            if(i>0 && i<500000) record[i]=1;
        }
        for(int i=1; i<500000; i++){
            if(record[i]==0) return i;
        }
        delete[] record;
        return 1;
    }
};

int main() {
    Solution x;
    vector<int> candidates = {3,4,-1,1};
    // for(int i=10;i>0;i--) candidates.push_back(i);
    int a = x.firstMissingPositive(candidates) ;
    cout << a;
    return 0;
}
