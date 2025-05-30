// #include "../base/Node.h"
#include <bits/stdc++.h>

using namespace std;

class LRUCache {
public:
  explicit LRUCache(int capacity) { capacity_ = capacity; }

  int get(int key) {
    auto idx = nodeMap_.find(key);
    if (idx != nodeMap_.end()) {
      auto [k, it] = *idx;
      auto [_, v] = *it;
      linkList_.erase(it);
      linkList_.emplace_front(k, v);
      nodeMap_[k] = linkList_.begin();
      return v;
    }
    return -1;
  }

  void put(int key, int value) {
    if (nodeMap_.find(key)!=nodeMap_.end()){
      int _ = get(key);
      linkList_.front().second = value;
      return;
    }
    if (linkList_.size() < capacity_) {
      linkList_.emplace_front(key, value);
      nodeMap_[key] = linkList_.begin();
    } else {
      int del_key = linkList_.back().first;
      nodeMap_.erase(del_key);
      linkList_.pop_back();
      linkList_.emplace_front(key, value);
      nodeMap_[key] = linkList_.begin();
    }
  }

private:
  list<pair<int, int>> linkList_;
  using iterator = decltype(linkList_.begin());
  unordered_map<int, iterator> nodeMap_;
  int capacity_ = 0;
};



int main() {
  LRUCache lru(2);
  lru.put(2, 2);
  lru.put(1, 1);
  cout << (lru.get(2)) << endl;
  lru.put(4, 4);
  cout << (lru.get(1)) << endl;
  cout << (lru.get(2)) << endl;

  cout << 1;
  return 0;
}