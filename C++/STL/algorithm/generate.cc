// generate 对序列所有元素原地应用一个可调用对象，生成新序列版本的为transform

#include <iostream>
#include <algorithm>

using namespace std;

int main() {

    string chars (30, ' '); // 30 space characters
    char ch = 'a';
    int incr = 0;
    std::generate ( std::begin (chars),
                    std::end (chars),
                    [ch, &incr]{ incr += 1; return ch + (incr % 26);});
    cout << chars << endl;

    string chars2 (30, ' '); // 30 space characters
    std::generate_n(std::begin (chars),
                    chars.size()/2,
                    []{ return ' ';});
    cout << chars << endl;


}


