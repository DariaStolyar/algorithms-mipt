// В задаче необходимо реализовать декартово дерево с операциями:
// insert, delete, exists, next, prev, kth(k-ая пор. статистика)

#include <algorithm>
#include <iostream>
#include <optional>
#include <random>
#include <string>
#include <vector>

struct Node {
  int key = 0;
  int priority = rand();
  int size = 0;
  Node* left_son = nullptr;
  Node* right_son = nullptr;
};

std::vector<Node*> all_nodes;

void ChangeSize(Node* head) {
  if (head->left_son == nullptr and head->right_son == nullptr) {
    head->size = 1;
  } else if (head->left_son == nullptr) {
    head->size = 1 + head->right_son->size;
  } else if (head->right_son == nullptr) {
    head->size = 1 + head->left_son->size;
  } else {
    head->size = 1 + head->right_son->size + head->left_son->size;
  }
}

Node* Merge(Node* left, Node* right) {
  if (left == nullptr) {
    return right;
  }
  if (right == nullptr) {
    return left;
  }
  if (left->priority < right->priority) {
    left->right_son = Merge(left->right_son, right);
    ChangeSize(left);
    return left;
  }
  right->left_son = Merge(left, right->left_son);
  ChangeSize(right);
  return right;
}

std::pair<Node*, Node*> Split(Node* head, int value) {
  if (head == nullptr) {
    return {nullptr, nullptr};
  }
  if (head->key <= value) {
    if (head->right_son == nullptr) {
      return {head, nullptr};
    }
    std::pair<Node*, Node*> result = Split(head->right_son, value);
    head->right_son = result.first;
    ChangeSize(head);
    return {head, result.second};
  }
  if (head->left_son == nullptr) {
    return {nullptr, head};
  }
  std::pair<Node*, Node*> result = Split(head->left_son, value);
  head->left_son = result.second;
  ChangeSize(head);
  return {result.first, head};
}

bool Exist(Node* head, int element) {
  Node* node = head;
  if (head == nullptr) {
    return false;
  }
  while (node != nullptr) {
    if (node->key == element) {
      return true;
    }
    if (node->key < element) {
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

Node* Insert(Node* head, int new_element) {
  if (Exist(head, new_element)) {
    return head;
  }
  std::pair<Node*, Node*> result = Split(head, new_element);
  Node* node = new Node;
  node->size = 1;
  node->key = new_element;
  all_nodes.push_back(node);
  return Merge(result.first, Merge(node, result.second));
}

Node* Erase(Node* head, int element) {
  if (!Exist(head, element)) {
    return head;
  }
  std::pair<Node*, Node*> result = Split(head, element);
  return Merge(Split(result.first, element - 1).first, result.second);
}

std::optional<int> Next(Node* head, int value) {
  Node* node = head;
  std::optional<int> normal_value = std::nullopt;
  while (node != nullptr) {
    if (node->key <= value) {
      if (node->right_son == nullptr) {
        if (normal_value) {
          return normal_value;
        }
        return {};
      }
      node = node->right_son;
      continue;
    }
    if (node->left_son == nullptr) {
      return node->key;
    }
    if (!normal_value) {
      normal_value = node->key;
    }
    normal_value.value() = std::min(node->key, normal_value.value());
    node = node->left_son;
  }
  return {};
}

std::optional<int> Prev(Node* head, int value) {
  Node* node = head;
  std::optional<int> normal_value = std::nullopt;
  while (node != nullptr) {
    if (node->key >= value) {
      if (node->left_son == nullptr) {
        if (normal_value) {
          return normal_value;
        }
        return {};
      }
      node = node->left_son;
      continue;
    }
    if (node->right_son == nullptr) {
      return node->key;
    }
    normal_value.value() = std::max(node->key, normal_value.value());
    node = node->right_son;
  }
  return {};
}

std::optional<int> Kth(Node* head, int number) {
  Node* node = head;
  int add = 0;
  if (head == nullptr) {
    return {};
  }
  if (head->size <= number) {
    return {};
  }
  if (number < 0) {
    return {};
  }
  while (node != nullptr) {
    if (node->left_son != nullptr and add + node->left_son->size > number) {
      node = node->left_son;
      continue;
    }
    if (node->left_son == nullptr and number == add) {
      return node->key;
    }
    if (node->left_son != nullptr and number == add + node->left_son->size) {
      return node->key;
    }
    if (node->left_son == nullptr) {
      add += 1;
    } else {
      add += node->left_son->size + 1;
    }
    node = node->right_son;
  }
  return {};
}
Node* QueryProcess(std::string query, Node* head, int number) {
  if (query == "insert") {
    head = Insert(head, number);
  }
  if (query == "delete") {
    head = Erase(head, number);
  }
  if (query == "exists") {
    if (Exist(head, number)) {
      std::cout << "true\n";
    } else {
      std::cout << "false\n";
    }
  }
  if (query == "next") {
    std::optional<int> next = Next(head, number);
    if (next) {
      std::cout << next.value() << "\n";
    } else {
      std::cout << "none\n";
    }
  }
  if (query == "prev") {
    std::optional<int> prev = Prev(head, number);
    if (prev) {
      std::cout << prev.value() << "\n";
    } else {
      std::cout << "none\n";
    }
  }
  if (query == "kth") {
    std::optional<int> kth = Kth(head, number);
    if (kth) {
      std::cout << kth.value() << "\n";
    } else {
      std::cout << "none\n";
    }
    Kth(head, number);
  }
  return head;
}

void BoostIO() {
  std::ios::sync_with_stdio(false);
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
}

int main() {
  BoostIO();
  std::string query;
  int number = 0;
  Node* head = nullptr;
  while (std::cin >> query) {
    std::cin >> number;
    head = QueryProcess(query, head, number);
  }
  for (size_t i = 0; i < all_nodes.size(); ++i) {
    delete all_nodes[i];
  }
}
