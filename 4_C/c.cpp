// В задаче необходимо реализовать структуру,
// сопоставляющую две строки друг другу

#include <algorithm>
#include <iostream>
#include <random>
#include <string>
#include <vector>

struct Node {
  std::string key;
  int priority = rand();
  std::string value;
  Node* left_son = nullptr;
  Node* right_son = nullptr;
};

std::vector<Node*> all_nodes;

Node* Merge(Node* left, Node* right) {
  if (left == nullptr) {
    return right;
  }
  if (right == nullptr) {
    return left;
  }
  if (left->priority < right->priority) {
    left->right_son = Merge(left->right_son, right);
    return left;
  }
  right->left_son = Merge(left, right->left_son);
  return right;
}

std::pair<Node*, Node*> Split(Node* head, std::string value) {
  if (head == nullptr) {
    return {nullptr, nullptr};
  }
  if (head->key <= value) {
    if (head->right_son == nullptr) {
      return {head, nullptr};
    }
    std::pair<Node*, Node*> result = Split(head->right_son, value);
    head->right_son = result.first;
    return {head, result.second};
  }
  if (head->left_son == nullptr) {
    return {nullptr, head};
  }
  std::pair<Node*, Node*> result = Split(head->left_son, value);
  head->left_son = result.second;
  return {result.first, head};
}

Node* Exist(Node* head, std::string element) {
  Node* node = head;
  if (head == nullptr) {
    return nullptr;
  }
  while (node != nullptr) {
    if (node->key == element) {
      return node;
    }
    if (node->key < element) {
      if (node->right_son == nullptr) {
        return nullptr;
      }
      node = node->right_son;
      continue;
    }
    if (node->left_son == nullptr) {
      return nullptr;
    }
    node = node->left_son;
  }
  return nullptr;
}

Node* Insert(Node* head, std::string new_element, std::string value) {
  if (Exist(head, new_element) != nullptr) {
    return head;
  }
  std::pair<Node*, Node*> result = Split(head, new_element);
  Node* node = new Node;
  node->key = new_element;
  node->value = value;
  all_nodes.push_back(node);
  return Merge(result.first, Merge(node, result.second));
}

void BoostIO() {
  std::ios::sync_with_stdio(false);
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
}

int main() {
  BoostIO();
  size_t count;
  std::cin >> count;
  Node* head1 = nullptr;
  Node* head2 = nullptr;
  for (size_t i = 0; i < count; ++i) {
    std::string rider;
    std::string car;
    std::cin >> rider >> car;
    head1 = Insert(head1, rider, car);
    head2 = Insert(head2, car, rider);
  }
  size_t count_query;
  std::cin >> count_query;
  for (size_t i = 0; i < count_query; ++i) {
    std::string query;
    std::cin >> query;
    if (Exist(head1, query) != nullptr) {
      std::cout << Exist(head1, query)->value << "\n";
    } else {
      std::cout << Exist(head2, query)->value << "\n";
    }
  }
  for (size_t i = 0; i < all_nodes.size(); ++i) {
    delete all_nodes[i];
  }
}
