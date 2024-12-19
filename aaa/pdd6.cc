#include <iostream>
#include <set>
#include <vector>
#include <string>

using namespace std;

// 函数声明
string findKthSubstring(const string &s, int k);

int main() {
    string s = "abc";
    int k = 3;

    // 查找第k小的子串
    string result = findKthSubstring(s, k);
    
    // 输出结果
    cout << "The " << k << "th smallest substring is: " << result << endl;

    return 0;
}

// 查找第k小的不同子串
string findKthSubstring(const string &s, int k) {
    set<string> substrings;

    // 生成所有不同的子串
    for (int i = 0; i < s.length(); ++i) {
        for (int j = i + 1; j <= s.length(); ++j) {
            substrings.insert(s.substr(i, j - i));
        }
    }

    // 将子串存入向量并排序
    vector<string> sortedSubstrings(substrings.begin(), substrings.end());
    
    // 返回第k小的子串（注意k是从1开始）
    if (k <= sortedSubstrings.size()) {
        return sortedSubstrings[k - 1];
    } else {
        return "";  // 如果k超出范围，返回空字符串
    }
}

/*

对于一个字符串s，所有不同的子串中，第k小的是什
示例1输入: aab 4
输出:ab
说明:字符串aab的子串从小到大依次为a aa aab ab b

示例2输入: abc 3
输出:abc
说明:字符串abc的子串从小到大依次为a ab abc b bc c

*/
