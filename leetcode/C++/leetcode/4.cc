#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int mid1,mid2,dellen=-1;
        int l1=0,r1=nums1.size()-1,l2=0,r2=nums2.size()-1;
        while(r1-l1>1 && r2-l2>1){
            mid1=(r1+l1)/2;
            mid2=(r2+l2)/2;
            if(nums1[mid1]>nums2[mid2]){
                dellen = min(r1-mid1,mid2-l2);
                if((r1-l1)%2+(r2-l2)%2==2 && dellen>1) dellen-=1;
                r1-=dellen;
                l2+=dellen;
            }
            else if(nums1[mid1]<nums2[mid2]){
                dellen = min(mid1-l1,r2-mid2);
                if((r1-l1)%2+(r2-l2)%2==2 && dellen>1) dellen-=1;
                l1+=dellen;
                r2-=dellen;
            }
            else{
                dellen=min(r1-l1,r2-l2)/2;
                l1+=dellen;
                r1-=dellen;
                l2+=dellen;  
                r2-=dellen;
            }
            if(dellen==0) break;
        }
        vector<int> less_num;
        if(r1-l1>1){
            if(r1-l1>=3) {
                dellen=(r1-l1)/2-1;
                l1+=dellen;
                r1-=dellen;
            }
        }
        else {            
            if(r2-l2>=3) {
                dellen=(r2-l2)/2-1;
                l2+=dellen;
                r2-=dellen;
            }
        }
        for(int i=l1;i<=r1;i++) less_num.push_back(nums1[i]);
        for(int i=l2;i<=r2;i++) less_num.push_back(nums2[i]);
        sort(less_num.begin(),less_num.end());
        
        double res;
        int n=less_num.size();
        if(n%2) res=less_num[n/2];
        else {
            res=less_num[n/2]+less_num[n/2-1];
            res/=2;
        }
        return res;
    }
};

int main() {
    Solution x;
    vector<int> nums1={1,5,6,7};
    vector<int> nums2={2,3,4,8,9,10};
    double a = x.findMedianSortedArrays(nums1,nums2);
    return 0;
}
