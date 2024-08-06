// inner_product 求内积, 0为初值

#include <iostream>
#include <numeric>
#include <vector>

int main() {
    std::vector<int> v1 = {1, 2, 3};
    std::vector<int> v2 = {4, 5, 6};

    int result = std::inner_product(v1.begin(), v1.end(), v2.begin(), 0);

    std::cout << "Inner product of v1 and v2: " << result << std::endl;

    return 0;
}