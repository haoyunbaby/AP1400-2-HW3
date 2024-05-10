#include "bst.h"

#include <functional>
#include <initializer_list>
#include <iomanip>
#include <iostream>
#include <memory>
#include <queue>
#include <stdexcept>
#include <vector>

using namespace std;

BST::Node::Node() : value(0), left(nullptr), right(nullptr) {}

BST::Node::Node(int value, Node *left = nullptr, Node *right = nullptr)
    : value(value), left(left), right(right) {}
// deep copy is not the HW3 want
// BST::Node::Node(const Node &node)
//     : value(node.value), left(nullptr), right(nullptr) {
//   if (node.left) {
//     left = new Node(*node.left);
//   }
//   if (node.right) {
//     right = new Node(*node.right);
//   }
// }
BST::Node::Node(const Node &node)
    : value(node.value), left(node.left), right(node.right) {}
ostream &operator<<(ostream &os, const BST::Node &node) {
  os << left;
  os << setw(17) << &node;
  os << "=> value:";
  os << setw(10) << node.value;
  os << "left:";
  os << setw(16) << node.left;
  os << "right:";
  os << setw(17) << node.right;
  os << '\n';
  return os;
}

bool BST::Node::operator==(const int &val) const { return value == val; }
bool BST::Node::operator!=(const int &val) const { return !(*this == val); }
bool BST::Node::operator<(const int &val) const { return value < val; }
bool BST::Node::operator>=(const int &val) const { return !(*this < val); }
bool BST::Node::operator>(const int &val) const { return value > val; }
bool BST::Node::operator<=(const int &val) const { return !(*this > val); }
bool operator==(const int &val, const BST::Node &node) { return node == val; }
bool operator!=(const int &val, const BST::Node &node) { return node != val; }
bool operator<(const int &val, const BST::Node &node) {
  return val < node.value;
}
bool operator>=(const int &val, const BST::Node &node) { return !(val < node); }
bool operator>(const int &val, const BST::Node &node) {
  return val > node.value;
}
bool operator<=(const int &val, const BST::Node &node) { return !(val > node); }

BST::BST() : root(nullptr) {}
BST::BST(BST &other) {
  Node *o_root = other.root;
  if (o_root) {
    queue<Node *> dq, o_dq;
    root = new Node(o_root->value);
    dq.push(root);
    o_dq.push(o_root);
    while (!o_dq.empty()) {
      Node *node = dq.front();
      dq.pop();
      Node *o_node = o_dq.front();
      o_dq.pop();
      if (o_node->left) {
        node->left = new Node(o_node->left->value);
        dq.push(node->left);
        o_dq.push(o_node->left);
      }
      if (o_node->right) {
        node->right = new Node(o_node->right->value);
        dq.push(node->right);
        o_dq.push(o_node->right);
      }
    }
  } else {
    root = nullptr;
  }
}
BST::BST(BST &&other) : root(other.root) { other.root = nullptr; }
BST::BST(const initializer_list<int> &list) : root(nullptr) {
  for (const int &x : list) {
    add_node(x);
  }
}
BST &BST::operator=(BST &other) {
  if (this == &other) {
    return *this;
  }
  vector<Node *> nodes;
  bfs([&](Node *&node) { nodes.push_back(node); });
  for (auto &node : nodes) {
    delete node;
  }
  auto o_root = other.root;
  if (o_root) {
    queue<Node *> dq, o_dq;
    root = new Node(o_root->value);
    dq.push(root);
    o_dq.push(o_root);
    while (!o_dq.empty()) {
      Node *node = dq.front();
      dq.pop();
      Node *o_node = o_dq.front();
      o_dq.pop();
      if (o_node->left) {
        node->left = new Node(o_node->left->value);
        dq.push(node->left);
        o_dq.push(o_node->left);
      }
      if (o_node->right) {
        node->right = new Node(o_node->right->value);
        dq.push(node->right);
        o_dq.push(o_node->right);
      }
    }
  } else {
    root = nullptr;
  }
  return *this;
}
BST &BST::operator=(BST &&other) {
  if (this == &other) {
    return *this;
  }
  vector<Node *> nodes;
  bfs([&](Node *&node) { nodes.push_back(node); });
  for (auto &node : nodes) {
    delete node;
  }
  root = other.root;
  other.root = nullptr;
  return *this;
}
BST::Node *&BST::get_root() { return root; }
void BST::bfs(function<void(Node *&node)> func) {
  if (!root) {
    return;
  }
  queue<Node *> dq;
  dq.push(root);
  while (!dq.empty()) {
    int n = dq.size();
    for (int i = 0; i < n; i++) {
      auto node = dq.front();
      dq.pop();
      func(node);
      if (node->left) {
        dq.push(node->left);
      }
      if (node->right) {
        dq.push(node->right);
      }
    }
  }
}
size_t BST::length() {
  size_t len = 0;
  bfs([&](Node *&node) { len++; });
  return len;
}
bool BST::add_node(int value) {
  Node *cur = root;
  if (!cur) {
    root = new Node(value);
    return true;
  }
  while (1) {
    if (*cur == value) {
      return false;
    }
    if (*cur < value) {
      if (cur->right) {
        cur = cur->right;
      } else {
        cur->right = new Node(value);
        return true;
      }
    }
    if (*cur > value) {
      if (cur->left) {
        cur = cur->left;
      } else {
        cur->left = new Node(value);
        return true;
      }
    }
  }
}
BST::Node **BST::find_node(int value) {
  if (!root) {
    return nullptr;
  }
  Node **pc = &root;
  while (*pc) {
    if (**pc == value) {
      return pc;
    }
    if (**pc < value) {
      pc = &(*pc)->right;
    } else {
      pc = &(*pc)->left;
    }
  }
  return nullptr;
}
BST::Node **BST::find_parrent(int value) {
  if (!root) {
    return nullptr;
  }
  if (*root == value) {
    return nullptr;
  }
  Node **pre;
  Node **pc = &root;
  while (*pc) {
    if (**pc == value) {
      return pre;
    }
    pre = pc;
    if (**pc < value) {
      pc = &(*pc)->right;
    } else {
      pc = &(*pc)->left;
    }
  }
  return nullptr;
}
BST::Node **BST::find_successor(int value) {
  Node **cur = find_node(value);
  if ((*cur)->left) {
    Node **t = &((*cur)->left);
    while ((*t)->right) {
      t = &(*t)->right;
    }
    return t;
  }
  Node **pre = find_parrent(value);
  while (*pre && *cur == (*pre)->left) {
    pre = cur;
    cur = find_parrent((*pre)->value);
  }
  return pre;
}
bool BST::delete_node(int value) {
  Node **cur = find_node(value);
  if (!cur) {
    return false;
  }
  Node *to_delete = *cur;

  if ((*cur)->left && (*cur)->right) {
    Node **suc = find_successor(value);
    int t = (*suc)->value;
    delete_node(t);
    (*cur)->value = t;
  } else {
    Node *child = (*cur)->left ? (*cur)->left : (*cur)->right;
    if (cur == &root) {
      root = child;
    } else {
      Node **pre = find_parrent(value);
      if ((*pre)->left == to_delete) {
        (*pre)->left = child;
      } else {
        (*pre)->right = child;
      }
    }
    delete to_delete;
    *cur = child;
  }
  return true;
}

ostream &operator<<(ostream &os, BST &bst) {
  os << string(80, '*') << '\n';
  bst.bfs([&](BST::Node *&node) { os << *node; });
  os << "binary search tree size: ";
  os << bst.length() << '\n';
  os << string(80, '*') << '\n';
  return os;
}
//  ********************************************************************************
//  0x188dee70       => value:25        left:0x188dedd0      right:0x188dedf0
//  0x188dedd0       => value:10        left:0x188dee30      right:0x188ded90
//  0x188dedf0       => value:50        left:0               right:0x188dee50
//  0x188dee30       => value:7         left:0               right:0
//  0x188ded90       => value:15        left:0               right:0
//  0x188dee50       => value:53        left:0               right:0
//  binary search tree size: 6
//  ********************************************************************************
BST &BST::operator++() {
  bfs([](Node *&node) { node->value++; });
  return *this;
}
BST BST::operator++(int) {
  BST rv{*this};
  ++*this;
  return rv;
}
BST::~BST() {
  vector<Node *> nodes;
  bfs([&](Node *&node) { nodes.push_back(node); });
  for (auto &node : nodes) {
    delete node;
  }
}
