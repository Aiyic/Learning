#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long maxScore(vector<int>& nums1, vector<int>& nums2, int k) {
        // 构建新数组去排序nums2
        vector<pair<int, int>> nums;
        int n = nums1.size();
        for (int i = 0; i < n; ++i)
        {
            nums.push_back({nums1[i], nums2[i]});
        }
        // 按照num2降序排列
        sort(nums.begin(), nums.end(), [](pair<int,int>& x, pair<int, int>& y)
        {
            return x.second > y.second;
        });

        // 优先级队列，保存最大k个num1
        priority_queue<int, vector<int>, greater<int>> pq1;
        long sum1 = 0;
        for (int i = 0; i < k; ++i)
        {
            sum1 += (long)nums[i].first;
            pq1.push(nums[i].first);
        }
        // 已经排序，这个时候最小的就是k-1
        long res = sum1 * nums[k-1].second;
        for (int i = k; i < n; ++i)
        {
            // 直插入更大的
            if (nums[i].first > pq1.top())
            {
                sum1 -= pq1.top() - nums[i].first;
                pq1.pop();
                pq1.push(nums[i].first);
            }
            res = max(res, sum1 * nums[i].second);
        }
        
        return res;
    }

    // long long maxScore(vector<int>& nums1, vector<int>& nums2, int k) {
    //     int sum=0,i;
    //     for(i=0;i<k;i++){
    //         sum += nums1[i];
    //     }
    //     int minn=INT_MAX;
    //     int minidx=-1;

    //     function<void(int,int)> find_min = [&](int left, int right){
    //         for(int x=left; x<right; x++){
    //             if(nums2[x]<minn){
    //                 minidx=x;
    //                 minn=nums2[x];
    //             }
    //         }
    //     };

    //     find_min(0,k);
    //     int res=sum*minn;
    //     for(i=0; i+k<nums1.size(); ++i){
    //         sum = sum - nums1[i] + nums1[i+k];

    //         if(i==minidx){
    //             find_min(i+1,i+k+1);
    //         }

    //         res = max(res,sum*minn);
    //     }
    //     return res;
    // }
};


int main() {
    Solution s;
    vector<int> nums1 = {1,3,3,2};
    vector<int> nums2 = {2,1,3,4};
    auto a = s.maxScore(nums1,nums2,3) ;
    cout << 1;
    return 0;
}
