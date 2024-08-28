
// partition()将满足条件的元素放在序列前段, stable_partition为稳定版本, 都是原地分组
// partition_copy()分别取出满足的元素和不满足的元素构成新的2个序列
// partition_point()返回已分组的序列分界点

#include <iostream>
#include <algorithm>

using namespace std;

bool mycomp(int x){
    return (x % 2 == 0);
}

int main() {

    vector<int> myvector{ 1,2,3,4,5,6,7,8,9 };

    // auto it = partition(myvector.begin(),myvector.end(),mycomp);
    auto it = stable_partition(myvector.begin(),myvector.end(),mycomp);

    int b[10] = { 0 }, c[10] = { 0 };
    //以 mycomp 规则，对 myvector 容器中的数据进行分组，这里的 mycomp 还可以改为 mycomp2()，即以 mycomp2 为筛选规则
    pair<int*, int*> result= partition_copy(myvector.begin(), myvector.end(), b, c, mycomp);

    for(auto & x : myvector)
        cout << x << ' ';
    cout << endl;

    it = partition_point(myvector.begin(), myvector.end(),mycomp);
    cout << *it << endl;
}

