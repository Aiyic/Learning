// accumulate 求和或自定义统计计算 位于 numeric  

#include <numeric>
#include <vector>
#include <iostream>

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    int sum = std::accumulate(numbers.begin(), numbers.end(), 0, [](int x, int y) { return x + y; });
    std::cout << "Sum: " << sum << std::endl;
    return 0;
}
