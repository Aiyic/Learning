#include <bits/stdc++.h>
#include <climits>
#include <ranges>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;
    map<int,bool> mouse;

    while((n--) != 0){
        int idx;
        bool ganran;
        cin >> idx >> ganran;
        mouse[idx] = ganran; 
    }
    int des=INT_MAX;
    int last_k=INT_MIN;
    for(auto [k,v] : mouse){
        if(!v){
            des = min(des,k-last_k);
        }
        else{
            last_k=k;
        }
    }
    last_k=INT_MAX;
    for(auto [k, v] : ranges::reverse_view(mouse)){
        if(!v){
            des = min(des,last_k-k);
        }
        else{
            last_k=k;
        }
    }

    int count=0;
    int left_idx=INT_MIN;
    for(auto [k,v] : mouse){
        if(v && left_idx+des<=k){
            left_idx=k;
            count++;
        }
    }
    cout << count;
}

/*

6
7 1
1 1
15 1
3 1
10 0
5 0


1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
1   1     1 1     0              1   

1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
1   1   0   1     0              1   


*/