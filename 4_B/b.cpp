// В задаче необходимо реализовать AVL-дерево

#include <algorithm>
#include <iostream>
#include <random>
#include <string>
#include <vector>

struct Node {
  int value = 0;
  int heigth = 0;
  Node* left_son = nullptr;
  Node* right_son = nullptr;
};

struct AVL {
  Node* head = nullptr;
  std::vector<Node*> all_nodes;
  const int kMin = -1e9 - 1;
  static void ChangeHeight(Node* node) {
    if (node->left_son == nullptr and node->right_son == nullptr) {
      node->heigth = 1;
    } else if (node->left_son == nullptr) {
      node->heigth = 1 + node->right_son->heigth;
    } else if (node->right_son == nullptr) {
      node->heigth = 1 + node->left_son->heigth;
    } else {
      node->heigth =
          1 + std::max(node->right_son->heigth, node->left_son->heigth);
    }
  }
  static int GetHeight(Node* node) {
    if (node == nullptr) {
      return 0;
    }
    ChangeHeight(node);
    return node->heigth;
  }
  static int GetDelta(Node* node) {
    if (node == nullptr) {
      return 0;
    }
    return GetHeight(node->left_son) - GetHeight(node->right_son);
  }
  static Node* SmallLeftChange(Node* node) {
    Node* son = node->right_son;
    node->right_son = son->left_son;
    son->left_son = node;
    ChangeHeight(node);
    ChangeHeight(son);
    return son;
  }
  static Node* SmallRightChange(Node* node) {
    Node* son = node->left_son;
    node->left_son = son->right_son;
    son->right_son = node;
    ChangeHeight(node);
    ChangeHeight(son);
    return son;
  }
  static Node* BigLeftChange(Node* node) {
    node->right_son = SmallRightChange(node->right_son);
    return SmallLeftChange(node);
  }
  static Node* BigRightChange(Node* node) {
    node->left_son = SmallLeftChange(node->left_son);
    return SmallRightChange(node);
  }
  bool Exist(int element) const {
    Node* node = head;
    while (node != nullptr) {
      if (node->value == element) {
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
  Node* Addition(Node* node, int new_element) {
    if (node == nullptr) {
      node = new Node;
      node->value = new_element;
      node->heigth = 1;
      all_nodes.push_back(node);
      return node;
    }
    if (node->value > new_element) {
      node->left_son = Addition(node->left_son, new_element);
    } else {
      node->right_son = Addition(node->right_son, new_element);
    }
    ChangeHeight(node);
    int delta_height = GetDelta(node);
    if (delta_height == -2) {
      if (GetDelta(node->right_son) != 1) {
        node = SmallLeftChange(node);
      } else {
        node = BigLeftChange(node);
      }
    }
    if (delta_height == 2) {
      if (GetDelta(node->left_son) != -1) {
        node = SmallRightChange(node);
      } else {
        node = BigRightChange(node);
      }
    }
    ChangeHeight(node);
    return node;
  }
  void Add(int new_element) {
    if (Exist(new_element)) {
      return;
    }
    head = Addition(head, new_element);
  }
  int Next(int value) const {
    if (Exist(value)) {
      std::cout << value << "\n";
      return value;
    }
    Node* node = head;
    int normal_value = kMin;
    while (node != nullptr) {
      if (node->value <= value) {
        if (node->right_son == nullptr) {
          if (normal_value != kMin) {
            std::cout << normal_value << "\n";
            return normal_value;
          }
          std::cout << "-1\n";
          return -1;
        }
        node = node->right_son;
        continue;
      }
      if (node->left_son == nullptr) {
        std::cout << node->value << "\n";
        return node->value;
      }
      if (normal_value == kMin) {
        normal_value = node->value;
      }
      normal_value = std::min(node->value, normal_value);
      node = node->left_son;
    }
    std::cout << "-1\n";
    return -1;
  }
  ~AVL() {
    for (size_t i = 0; i < all_nodes.size(); ++i) {
      delete all_nodes[i];
    }
  }
};

void Speed() {
  std::ios::sync_with_stdio(false);
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
}

int main() {
  Speed();
  const int kMax = 1e9;
  size_t count_query;
  std::cin >> count_query;
  long long last_query = -2;
  AVL avl;
  for (size_t i = 0; i < count_query; ++i) {
    std::string query;
    std::cin >> query;
    if (query == "+") {
      int number;
      std::cin >> number;
      if (last_query == -2) {
        avl.Add(number);
      } else {
        avl.Add((number + last_query) % kMax);
      }
      last_query = -2;
    } else {
      int car;
      std::cin >> car;
      last_query = avl.Next(car);
    }
  }
}
