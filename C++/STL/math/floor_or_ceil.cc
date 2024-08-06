// y=ceil(x) 向上取整, y>=x
// y=floor(x) 向下取整 y<=x

#include <iostream>
#include <cmath>

using namespace std;

int main() {
    double x,y;

    x = ceil(1.5);
    y = floor(1.5);
    cout << x << ' ' << y << endl;

    x = ceil(-3.5);
    y = floor(-3.5);
    cout << x << ' ' << y << endl;
}

