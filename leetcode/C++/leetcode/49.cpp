#include<iostream>
#include<vector>
#include<stack>
#include<functional>
#include<algorithm>

using namespace std;

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        int n=strs.size();
        vector<vector<string>> result;
        vector<int> record(n);
        for(int i=0; i<n; i++){
            int h=1;
            for(char c : strs[i]){
                h+=c*c;
            }
            record[i]=h;
        }
        vector<bool> flag(n,false);
        for(int i=0; i<n; i++){
            if(flag[i]) continue;
            flag[i]=true;
            vector<string> vs={strs[i]};
            for(int j=i+1; j<n; j++){
                if(record[i]==record[j]){
                    vector<int> charN(26,0);
                    bool f=false;
                    for(char c : strs[i]) charN[c-'a']++;
                    for(char c : strs[j]) charN[c-'a']--;
                    for(int x : charN) if(x) f=true;
                    if(f) continue;
                    flag[j]=true;
                    vs.push_back(strs[j]);
                }
            }
            result.push_back(vs);
        }
        return result;
    }
};
int main() {
    Solution x;
    vector<string> strs={"run","had","lot","kim","fat","net","fin","rca","chi","lei","lox","iva","liz","hug","hot","irk","lap","tan","tux","yuk","hep","map","ran","ell","kit","put","non","aol","add","lad","she","job","mes","pen","vic","fag","bud","ken","nod","jam","coy","hui","sue","nap","ton","coy","rut","fit","cut","eta","our","oho","zip"};
    vector<vector<string>> a = x.groupAnagrams(strs) ;
    cout << 1;
    return 0;
}
