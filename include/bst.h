#include <functional>
#include <initializer_list>
#include <iostream>
#include <vector>
#ifndef BST_H
#define BST_H
class BST {
 public:
  class Node {
   public:
    Node(int value, Node *left, Node *right);
    Node();
    Node(const Node &node);

    int value;
    Node *left;
    Node *right;

    friend std::ostream &operator<<(std::ostream &os, const Node &node);
    bool operator==(const int &val) const;
    bool operator!=(const int &val) const;
    bool operator<(const int &val) const;
    bool operator>=(const int &val) const;
    bool operator>(const int &val) const;
    bool operator<=(const int &val) const;
  };
  Node *&get_root();
  void bfs(std::function<void(Node *&node)> func);
  size_t length();
  bool add_node(int value);
  Node **find_node(int value);
  Node **find_parrent(int value);
  Node **find_successor(int value);
  bool delete_node(int value);
  friend std::ostream &operator<<(std::ostream &os, BST &bst);
  BST();
  BST(BST &other);
  BST(BST &&other);
  // BST(const std::vector<int> &arr);
  BST(const std::initializer_list<int> &list);
  BST &operator=(BST &other);
  BST &operator=(BST &&other);
  ~BST();
  BST &operator++();    // pre-increment
  BST operator++(int);  // post-increment

 private:
  Node *root;
};
bool operator==(const int &val, const BST::Node &node);
bool operator!=(const int &val, const BST::Node &node);
bool operator<(const int &val, const BST::Node &node);
bool operator>=(const int &val, const BST::Node &node);
bool operator>(const int &val, const BST::Node &node);
bool operator<=(const int &val, const BST::Node &node);
#endif  // BST_H
