/*

stringToTree("[1,-2,null,1,3,-2,null,-1]");

*/

#include <queue>
#include <sstream>
#include <string>

#include "./ListNode.h"
#include "./TreeNode.h"

std::queue<std::string> stringToVector(const std::string &str) {
  std::queue<std::string> result;
  std::string cleaned_str = str.substr(1, str.size() - 2); // 去掉方括号
  std::stringstream ss(cleaned_str);
  std::string item;

  while (std::getline(ss, item, ',')) {
    result.push(item);
  }
  return result;
}

TreeNode *VectorToTree(std::queue<std::string> &v) {
  if (v.empty()) {
    return nullptr;
  }
  auto &root_val = v.front();
  v.pop();
  auto *root = new TreeNode(std::stoi(root_val));
  std::queue<TreeNode *> now;
  std::queue<TreeNode *> next;
  now.push(root);
  while (!now.empty()) {
    auto *parent = now.front();
    now.pop();
    if (v.empty()) {
      break;
    }
    std::string left_str = v.front();
    v.pop();
    if (left_str != "null") {
      parent->left = new TreeNode(std::stoi(left_str));
      next.push(parent->left);
    }
    if (v.empty()) {
      break;
    }
    std::string right_str = v.front();
    v.pop();
    if (right_str != "null") {
      parent->right = new TreeNode(std::stoi(right_str));
      next.push(parent->right);
    }
    if (now.empty()) {
      now.swap(next);
    }
  }
  return root;
}

inline TreeNode *stringToTree(const std::string &str) {
  auto v = stringToVector(str);
  return VectorToTree(v);
}


