#include<iostream>
#include<vector>
#include<stack>
#include<functional>
#include<algorithm>

using namespace std;

class Solution {
public:
    int trap(vector<int>& height) {
        return trap2(height,0,height.size()-1);
    }
    int trap2(vector<int>& height,int left,int right){
        if(left+1>=right) return 0;
        int high=0,mid=-1;
        for(int i=left+1; i<right; i++){
            if(height[i]>high) {
                high=height[i];
                mid=i;
            }
        }

        if(high<=height[left] && high<=height[right]){
            high = height[left]<height[right] ? height[left] : height[right];
            mid = 0;
            for(int i=left+1; i<right; i++)
                mid += high-height[i];
            return mid;
        }
        else return trap2(height,left,mid) + trap2(height,mid,right);
    }
};

int main() {
    Solution x;
    vector<int> height = {8,5,4,1,8,9,3,0,0};
    int a = x.trap(height) ;
    cout << a;
    return 0;
}
