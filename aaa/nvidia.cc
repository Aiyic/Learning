#include <bits/stdc++.h>
#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main() {
  string s;
  while (getline(cin, s)) {
    stringstream ss(s);
    char c;
    int number;
    while (ss.peek() != EOF) { 
        c = ss.peek();
        if (c >= '0' && c <= '9') {
            ss >> number; 
            break; 
        }
        ss >> c; 
    }
    string ti;
    getline(ss, ti, ' ');
    cout << ti;
  }
  return 0;
}

/*

NVIDIA GeForce RTX 4090 Founders Edition @ 2520 MHz
NVIDIA GeForce RTX 4090 Founders Edition Rev. 2 @ 2520 MHz
NVIDIA GeForce RTX 4080 Founders Edition @ 2505 MHz
NVIDIA GeForce RTX4070 Founders Edition @ 2475 MHz
NVIDIA GeForce RTX 4060 Ti Founders Edition @ 2535 MHz

*/