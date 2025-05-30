
#include<bits/stdc++.h>
using namespace std;

class UnionFind {
private:
    vector<int> roots;

public:
    UnionFind() {
        roots.resize(26);
        iota(roots.begin(), roots.end(), 0);
    }

    int find(int index) {
        if (index == roots[index]) {
            return index;
        }
        roots[index] = find(roots[index]);
        return roots[index];
    }

    void unite(int index1, int index2) {
        roots[find(index1)] = find(index2);
    }
};

class Solution {
public:
    bool equationsPossible(vector<string>& equations) {
        UnionFind uf;
        for (const string& str: equations) {
            if (str[1] == '=') {
                int index1 = str[0] - 'a';
                int index2 = str[3] - 'a';
                uf.unite(index1, index2);
            }
        }
        for (const string& str: equations) {
            if (str[1] == '!') {
                int index1 = str[0] - 'a';
                int index2 = str[3] - 'a';
                if (uf.find(index1) == uf.find(index2)) {
                    return false;
                }
            }
        }
        return true;
    }
};

int main() {
    Solution s;

    vector<string> equations={"a==b","e==c","b==c","a!=e"};
    auto a = s.equationsPossible(equations) ;
    cout << a;
    return 0;
}
