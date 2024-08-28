#include<bits/stdc++.h>
using namespace std;

class RecentCounter {
private:
    deque<int> pingque;
public:
    RecentCounter() {
        pingque.clear();
    }
    
    int ping(int t) {
        pingque.push_front(t);
        int res=0;
        auto it=pingque.begin();
        while(it!=pingque.end()){
            if(*it>=t-3000) res++;
            else break;
            it++;
        }
        return res;
    }
};

/**
 * Your RecentCounter object will be instantiated and called as such:
 * RecentCounter* obj = new RecentCounter();
 * int param_1 = obj->ping(t);
 */

int main() {
    RecentCounter RC;

    int a=RC.ping(1) ;
    cout << 1;
    return 0;
}
