#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include <stack>

using namespace std;

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        vector<int> res(temperatures.size());
        stack<int> idx;
        for(int i=0; i<temperatures.size(); ++i){
            if(idx.empty()){
                idx.push(i); continue;
            }
            else{
                if(temperatures[idx.top()]>=temperatures[i]) idx.push(i);
                else{
                    res[idx.top()]=i-idx.top();
                    idx.pop(); i--; 
                    continue;
                }
            }
        }
        while(!idx.empty()){
            res[idx.top()]=0;
            idx.pop();
        }
        return res;
    }


    vector<int> dailyTemperatures2(vector<int>& temperatures) {
        vector<int> res(temperatures.size());
        for(int i=0; i<temperatures.size(); ++i){
            int day=1;
            while(i+day < temperatures.size() && temperatures[i] >= temperatures[i+day]){ 
                day++;
            }
            if(i+day == temperatures.size()) res[i]=0;
            else res[i]=day;
        }
        return res;
    }
};


int main() {
    Solution s;
    vector<int> temperatures={73,74,75,71,69,72,76,73};
    auto a = s.dailyTemperatures(temperatures);
    cout << 1;
    return 0;
}
