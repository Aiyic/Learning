#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int compress(vector<char>& chars) {
        int idx=0;
        while(idx<chars.size()){
            int len=1,i=0,lenn;
            while(idx+len<chars.size() && chars[idx]==chars[idx+len]) len++;
            lenn=len;
            if(len>1){
                i=1;
                while(len){
                    chars[idx+i]=len%10+'0';
                    len=len/10;
                    i++;
                }
                i--;
                reverse(chars.begin()+idx+1,chars.begin()+idx+i+1);
                chars.erase(chars.begin()+idx+i+1,chars.begin()+idx+lenn);
            }
            idx=idx+i+1;
        }
        return chars.size();
    }
};

int main() {
    Solution s;
    vector<char> nums={'a','b','b','b','b','b','b','b','b','b'};
    int a = s.compress(nums) ;
    cout << 1;
    return 0;
}
