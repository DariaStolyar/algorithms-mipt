// В задаче необходимо реализовать структуру, 
// сопоставляющую две строки друг другу

#include <algorithm>
#include <iostream>
#include <random>
#include <string>
#include <vector>

struct Node {
  std::string value;
  int priority = rand();
  std::string second_value;
  Node* left_son = nullptr;
  Node* right_son = nullptr;
};

std::vector<Node*> all_nodes;

Node* Merge(Node* head1, Node* head2) {
  if (head1 == nullptr) {
    return head2;
  }
  if (head2 == nullptr) {
    return head1;
  }
  if (head1->priority < head2->priority) {
    head1->right_son = Merge(head1->right_son, head2);
    return head1;
  }
  head2->left_son = Merge(head1, head2->left_son);
  return head2;
}

std::pair<Node*, Node*> Split(Node* head, std::string value) {
  if (head == nullptr) {
    return {nullptr, nullptr};
  }
  if (head->value <= value) {
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

bool Exist(Node* head, std::string element) {
  Node* node = head;
  if (head == nullptr) {
    return false;
  }
  while (node != nullptr) {
    if (node->value == element) {
      std::cout << node->second_value << "\n";
      return true;
    }
    if (node->value < element) {
      if (node->right_son == nullptr) {
        return false;
      }
      node = node->right_son;
      continue;
    }
    if (node->left_son == nullptr) {
      return false;
    }
    node = node->left_son;
  }
  return false;
}

Node* Insert(Node* head, std::string new_element, std::string value) {
  if (Exist(head, new_element)) {
    return head;
  }
  std::pair<Node*, Node*> result = Split(head, new_element);
  Node* node = new Node;
  node->value = new_element;
  node->second_value = value;
  all_nodes.push_back(node);
  return Merge(result.first, Merge(node, result.second));
}

void Speed() {
  std::ios::sync_with_stdio(false);
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
}

int main() {
  Speed();
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
    Exist(head1, query);
    Exist(head2, query);
  }
  for (size_t i = 0; i < all_nodes.size(); ++i) {
    delete all_nodes[i];
  }
}
