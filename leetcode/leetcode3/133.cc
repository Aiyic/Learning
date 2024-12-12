// #include "../base/Node.h"
#include <bits/stdc++.h>

#include <unordered_map>
#include <utility>

using namespace std;


// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    explicit Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = std::move(_neighbors);
    }
};


class Solution {
public:
    static Node* cloneGraph(Node* node) {
        unordered_map<int, Node*> mapp;

        function<Node*(Node*)> dfs = [&](Node* node) -> Node* {
            if (node == nullptr) {
                return nullptr;
            }
            if (mapp.find(node->val) != mapp.end()) {
                return mapp[node->val];
            }
            Node* new_node = new Node(node->val);
            mapp[node->val] = new_node;
            for (auto& neighbor : node->neighbors) {
                new_node->neighbors.push_back(dfs(neighbor));
            }
            return new_node;
        };

        return dfs(node);
    }
};

int main() {
//   vector<int> arr= {1,2,3,4,4};
//   string s = "hello world";
  auto *a = Solution::cloneGraph(0);
  cout << 1;
  return 0;
}

/*

~

*/
