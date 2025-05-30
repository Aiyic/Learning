#include<iostream>
#include<vector>
#include<queue>

using namespace std;

class Solution {
public:
    class cmp{
    public:
        bool operator()(const int& a, const int& b ){
            return a>b;
        }
    };
    int findKthLargest(vector<int>& nums, int k)  {
        priority_queue<int, vector<int>, cmp> pq;
        for(int x : nums){
            if(pq.size()<k) pq.push(x);
            else {
                if(x>pq.top()){
                    pq.pop();
                    pq.push(x);
                }
            }
        }
        return pq.top();
    }

    int findKthLargest(vector<int>& nums, int k)  {
        vector<int> left,right;
        int mid=0;
        int key = rand()%k;

        for(int x:nums){
            if(nums[key]==x) mid++;
            else if(nums[key]<x) left.push_back(x);
            else right.push_back(x);
        }
        if(left.size()==0 && right.size()==0) 
            return nums[key];

        if(k<=left.size()) 
            return findKthLargest(left, k) ;
        else if(k<=left.size()+mid) 
            return nums[key];
        else 
            return findKthLargest(right, k-left.size()-mid) ;
    }
};

int main(){
    Solution solution;
    int k=4;
    vector<int> nums={3,2,3,1,2,4,5,5,6};
    int a = solution.findKthLargest(nums,k);
    cout << a;
    return 0;
}