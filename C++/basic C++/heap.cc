// std 维护堆性质函数
//    make_heap() 建立堆
//    push_heap() 先添加元素后, 使用其来维护堆结构
//    pop_heap() 调用后立即将堆顶移到尾部
//    is_heap() 判断序列是否为堆
//    sort_heap() 堆排序


#include <iostream>  
#include <algorithm>

using namespace std;

int main() {  

    vector<int>values{ 2,8,1,6,5,7,3,4 };
    make_heap(values.begin(), values.end()); 
    for_each(values.begin(), values.end(), [](int v){ std::cout << v << ' ';});
    std::cout << std::endl;

    values.push_back(9);
    push_heap(values.begin(), values.end());
    for_each(values.begin(), values.end(), [](int v){ std::cout << v << ' ';});
    std::cout << std::endl;

    std::cout << is_heap(values.begin(), values.end()) << std::endl; 

    pop_heap(values.begin(), values.end());
    pop_heap(values.begin(), values.end()-1);
    for_each(values.begin(), values.end(), [](int v){ std::cout << v << ' ';});
    std::cout << std::endl;

    sort_heap(values.begin(), values.end()-2);
    for_each(values.begin(), values.end(), [](int v){ std::cout << v << ' ';});
    std::cout << std::endl;

    return 0;  
} 
