#include<bits/stdc++.h>
using namespace std;

class Solution {
public:

    using ktype = pair<int,int>;
    struct cmp
    {
        bool operator()(const ktype &a, const ktype &b){
            if(a.first>b.first) return true;
            else if(a.first==b.first) return a.second>b.second;
            else return false;
        }
    };
    priority_queue<ktype,vector<ktype>,cmp> pq;

    long long totalCost(vector<int>& costs, int k, int candidates) {
        if(k==0) return 0;
        int n=costs.size();
        int left=candidates;
        int right=costs.size()-candidates;
        if(left<right){
            for(int i=0; i<left; ++i)
                pq.emplace(costs[i],i);
            
            for(int i=right; i<costs.size(); ++i)
                pq.emplace(costs[i],i);
        }
        else{
            for(int i=0; i<costs.size(); ++i)
                pq.emplace(costs[i],i);
        }

        return fun(costs,k,left,right);
    }

    long long fun(vector<int>& costs, int k, int left, int right){
        if(k<=0) return 0;

        auto t = pq.top();
        pq.pop();

        if(left<right){
            if(t.second<left){
                pq.emplace(costs[left],left);
                left++;
            }
            else if(t.second>=right) {
                right--;
                pq.emplace(costs[right],right);
            }
        }
        return fun(costs,k-1,left,right) + t.first;
    }
};


int main() {
    Solution s;
    vector<int> nums = {17,12,10,2,7,2,11,20,8};
    auto a = s.totalCost(nums,3,4) ;
    cout << a;
    return 0;
}
