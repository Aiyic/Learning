#include<bits/stdc++.h>
using namespace std;



class Solution {
public:
    int judge_add_or_sub(char c){
        return ((c=='+')||(c=='-'));
    }    
    int judge_point(char c){
        return (c=='.');
    }
    int judge_e(char c){
        return ((c=='e')||(c=='E'));
    }
    int judge_number(string s){
        int i=0;
        while(i<s.length() && s[i]>='0' && s[i]<='9') i++;
        return i;
    }

    int judge_small(string s){
        if(s.length()==0) return 0;
        int x=0;
        if(judge_add_or_sub(s[0])) x++;
        
        if(judge_point(s[x])){
            x++;
            int y=judge_number(string(s,x));
            if(y) return x+y;
            else return 0;
        }
        else{
            int y=judge_number(string(s,x));
            if(!y) return 0;
            int z=judge_point(s[x+y]);
            if(!z) return 0;
            return x+y+z+judge_number(string(s,x+y+z));
        }
    }
    int judge_integer(string s){
        if(s.length()==0) return 0;

        if(judge_add_or_sub(s[0])) {
            int x=judge_number(string(s,1));
            if(x) return x+1; 
        }
        else return judge_number(s);
        return 0;
    }

    bool isNumber(string s) {
        int x = judge_small(s);
        if(!x){
            x = judge_integer(s);
            if(!x) return false;
        } 
        s=string(s,x);
        if(s.length()==0) return true;

        if(judge_e(s[0])) s=string(s,1);
        else return false;
        
        x = judge_integer(s);
        if(!x) return false;

        if(s.length()==x) return true;
        else return false;
    }
};


int main() {
    Solution solution;
    string s = "-123.456e789";
    bool a = solution.isNumber(s) ;
    cout << a;
    return 0;
}