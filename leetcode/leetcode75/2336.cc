#include<bits/stdc++.h>
using namespace std;

class SmallestInfiniteSet {
public:
    SmallestInfiniteSet(): lower(1) {
        
    }
    
    int popSmallest() {
        if(!addnum.empty()){
            if(addnum[0]<lower) {
                int x = *addnum.begin();
                addnum.erase(addnum.begin());
                return x;
            }
        }
        return lower++;
    }
    
    void addBack(int num) {
        if(num >= lower) return;
        auto it = equal_range(addnum.begin(),addnum.end(),num);
        if(it.first!=it.second) return;
        addnum.insert(it.first, num);
    }
    
    deque<int> addnum;
    int lower;
};

int main() {
    SmallestInfiniteSet solution;
    solution.addBack(1);
    solution.popSmallest();

    cout << 1;
    return 0;
}






