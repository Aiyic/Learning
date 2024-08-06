#include <bits/stdc++.h>
#include <boost/format.hpp>

using namespace std;
using boost::format;

int main(){
    cout << boost::format("writing %1%,  x=%2% : %3%-th try") % "toto" % 40.23 % 50 << endl; 

    cout << format("%1% %2% %3% %2% %1% \n") % "11" % "22" % "333" << endl; // 'simple' style.
}