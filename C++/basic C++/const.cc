
#include <iostream>  
using namespace std;

int main() {  
    int x=1;
    int* const px = &x;
    const int* px2 = &x;

    const int y=1;
    auto py = &y;
    auto py2 = const_cast<int*>(py);
    (*py2)=20;
    return 0;  
} 
