#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

class StockSpanner {
public:
    StockSpanner(): idx(0) {}
    
    int next(int price) {
        idx++;
        int day=1;
        if(idxStack.empty())  day=idx;
        else{
            if(priceStack.back() <= price) {
                while(!priceStack.empty() && priceStack.back() <= price){
                    priceStack.erase(priceStack.end()-1);
                    idxStack.erase(idxStack.end()-1);
                }
                if(priceStack.empty()) day=idx;
                else day=idx-idxStack.back();
            }
        }
        idxStack.push_back(idx);
        priceStack.push_back(price);
        return day;
    }

    int idx;
    vector<int> idxStack;
    vector<int> priceStack;
};

/**
 * Your StockSpanner object will be instantiated and called as such:
 * StockSpanner* obj = new StockSpanner();
 * int param_1 = obj->next(price);
 */


int main() {
    StockSpanner* obj = new StockSpanner();
    int param_1 = obj->next(29);
    int param_2 = obj->next(91);
    int param_3 = obj->next(62);
    int param_4 = obj->next(79);
    int param_5 = obj->next(51);
    // int param_1 = obj->next(100);
    // int param_2 = obj->next(80);
    // int param_3 = obj->next(60);
    // int param_4 = obj->next(70);
    // int param_5 = obj->next(60);
    // int param_6 = obj->next(75);
    // int param_7 = obj->next(85);

    // cout << param_1 << ' '
    //     << param_2 << ' '
    //     << param_3 << ' '
    //     << param_4 << ' '
    //     << param_5 << ' ';
    return 0;
}
