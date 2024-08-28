#include <algorithm>
#include <bits/stdc++.h>
#include <vector>

using namespace std;

int main() {
    int t;
    cin >> t;
    while((t--) != 0){
        int n;
        cin >> n;

        vector<int> v(n);
        vector<int> w(n);
        for(int i=0;i<n;++i){
            cin >> v[i];
        }
        for(int i=0;i<n-1;++i){
            int tmp;
            cin >> tmp >> tmp >> w[i];
        }

        ranges::sort(w);

        int sum=0;
        for_each(w.begin(), w.end(), [&sum](int i){sum+=i;});
        int maxsum=sum;
        
        for(int i=0;i<n;++i){
            sum -= w[i];
            maxsum = max(maxsum, sum+v[i]);
        }
        cout << maxsum << endl;
    }
}