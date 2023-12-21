// В задаче необходимо реализовать структуру,
// сопоставляющую две строки друг другу

#include <algorithm>
#include <iostream>
#include <random>
#include <string>
#include <vector>

struct CartesianTree {
  std::string key;
  int priority = rand();
  std::string value;
  CartesianTree* left_son = nullptr;
  CartesianTree* right_son = nullptr;
};

CartesianTree* Merge(CartesianTree* left, CartesianTree* right) {
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

std::pair<CartesianTree*, CartesianTree*> Split(CartesianTree* head,
                                                std::string value) {
  if (head == nullptr) {
    return {nullptr, nullptr};
  }
  if (head->key <= value) {
    if (head->right_son == nullptr) {
      return {head, nullptr};
    }
    std::pair<CartesianTree*, CartesianTree*> result =
        Split(head->right_son, value);
    head->right_son = result.first;
    return {head, result.second};
  }
  if (head->left_son == nullptr) {
    return {nullptr, head};
  }
  std::pair<CartesianTree*, CartesianTree*> result =
      Split(head->left_son, value);
  head->left_son = result.second;
  return {result.first, head};
}

CartesianTree* Exist(CartesianTree* head, std::string element) {
  CartesianTree* node = head;
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

CartesianTree* Insert(CartesianTree* head, std::string new_element,
                      std::string value) {
  if (Exist(head, new_element) != nullptr) {
    return head;
  }
  std::pair<CartesianTree*, CartesianTree*> result = Split(head, new_element);
  CartesianTree* node = new CartesianTree;
  node->key = new_element;
  node->value = value;
  return Merge(result.first, Merge(node, result.second));
}

void Delete(CartesianTree* node) {
  if (node == nullptr) {
    return;
  }
  Delete(node->right_son);
  Delete(node->left_son);
  delete node;
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
  CartesianTree* head1 = nullptr;
  CartesianTree* head2 = nullptr;
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
  Delete(head1);
  Delete(head2);
}
