#include<bits/stdc++.h>
using namespace std;

class Solution {
public: 
    string predictPartyVictory(string senate) 
    {
        queue<int> R;
        queue<int> D;

        for(int i=0; i<senate.size(); i++)
        {
            if(senate[i] == 'R')
                R.push(i); 
            else
                D.push(i);
        }

        while(!R.empty() && !D.empty())
        {
            if(R.front() < D.front())
                R.push(R.front()+senate.size());
            else   
                D.push(D.front()+senate.size());
            
            R.pop();
            D.pop();
        }

        return !R.empty() ? "Radiant" : "Dire";
    }

    string predictPartyVictory2(string senate) {
        int state=0;
        for(auto i=senate.begin();i!=senate.end();i++){
            if(*i=='R'){
                state |= 1;
                bool flag=false;
                auto j=i;
                while(j!=senate.end()){
                    if(*j=='D'){
                        *j=' ';
                        flag=true;
                        break;
                    } 
                    else j++;
                }
                if(!flag){
                    j=senate.begin();
                    while(j!=i){
                        if(*j=='D'){
                            *j=' ';
                            break;
                        } 
                        else j++;
                    }
                }
            }
            else if(*i=='D'){
                state |= 2;
                bool flag=false;
                auto j=i;
                while(j!=senate.end()){
                    if(*j=='R'){
                        *j=' ';
                        flag=true;
                        break;
                    } 
                    else j++;
                }
                if(!flag){
                    j=senate.begin();
                    while(j!=i){
                        if(*j=='R'){
                            *j=' ';
                            break;
                        } 
                        else j++;
                    }
                }
            }
            else if(*i==' ') continue;
        }
        if(state==1) return "Radiant";
        else if(state==2) return "Dire";
        else return predictPartyVictory(senate);
    }
};

int main() {
    Solution s;
    string a = s.predictPartyVictory("DRRDRDRDRDDRDRDR") ;
    cout << 1;
    return 0;
}
/*

"DRRDRDRDRDDRDRDR"


*/