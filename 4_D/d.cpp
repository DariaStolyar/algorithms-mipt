#include <algorithm>
#include <iostream>
#include <random>
#include <string>
#include <vector>

struct Node {
  int value = 0;
  int priority = rand();
  int size = 0;
  Node* left_son = nullptr;
  Node* right_son = nullptr;
};

std::vector<Node*> all_nodes;
const int kMin = -1e9 - 1;

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

Node* Merge(Node* head1, Node* head2) {
  if (head1 == nullptr) {
    return head2;
  }
  if (head2 == nullptr) {
    return head1;
  }
  if (head1->priority < head2->priority) {
    head1->right_son = Merge(head1->right_son, head2);
    ChangeSize(head1);
    return head1;
  }
  head2->left_son = Merge(head1, head2->left_son);
  ChangeSize(head2);
  return head2;
}

std::pair<Node*, Node*> Split(Node* head, int value) {
  if (head == nullptr) {
    return {nullptr, nullptr};
  }
  if (head->value <= value) {
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

Node* Insert(Node* head, int new_element) {
  if (Exist(head, new_element)) {
    return head;
  }
  std::pair<Node*, Node*> result = Split(head, new_element);
  Node* node = new Node;
  node->size = 1;
  node->value = new_element;
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

void Next(Node* head, int value) {
  Node* node = head;
  int normal_value = kMin;
  while (node != nullptr) {
    if (node->value <= value) {
      if (node->right_son == nullptr) {
        if (normal_value != kMin) {
          std::cout << normal_value << "\n";
          return;
        }
        std::cout << "none\n";
        return;
      }
      node = node->right_son;
      continue;
    }
    if (node->left_son == nullptr) {
      std::cout << node->value << "\n";
      return;
    }
    if (normal_value == kMin) {
      normal_value = node->value;
    }
    normal_value = std::min(node->value, normal_value);
    node = node->left_son;
  }
  std::cout << "none\n";
}

void Prev(Node* head, int value) {
  Node* node = head;
  int normal_value = kMin;
  while (node != nullptr) {
    if (node->value >= value) {
      if (node->left_son == nullptr) {
        if (normal_value != kMin) {
          std::cout << normal_value << "\n";
          return;
        }
        std::cout << "none\n";
        return;
      }
      node = node->left_son;
      continue;
    }
    if (node->right_son == nullptr) {
      std::cout << node->value << "\n";
      return;
    }
    normal_value = std::max(node->value, normal_value);
    node = node->right_son;
  }
  std::cout << "none\n";
}

void Kth(Node* head, int number) {
  Node* node = head;
  int add = 0;
  if (head == nullptr) {
    std::cout << "none\n";
    return;
  }
  if (head->size <= number) {
    std::cout << "none\n";
    return;
  }
  if (number < 0) {
    std::cout << "none\n";
    return;
  }
  while (node != nullptr) {
    if (node->left_son != nullptr and add + node->left_son->size > number) {
      node = node->left_son;
      continue;
    }
    if (node->left_son == nullptr and number == add) {
      std::cout << node->value << "\n";
      return;
    }
    if (node->left_son != nullptr and number == add + node->left_son->size) {
      std::cout << node->value << "\n";
      return;
    }
    if (node->left_son == nullptr) {
      add += 1;
    } else {
      add += node->left_son->size + 1;
    }
    node = node->right_son;
  }
}

void Speed() {
  std::ios::sync_with_stdio(false);
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
}

int main() {
  Speed();
  std::string query;
  int number = 0;
  Node* head = nullptr;
  while (std::cin >> query) {
    if (query == ".") {
      break;
    }
    std::cin >> number;
    if (query == "insert") {
      if (head == nullptr) {
        head = new Node;
        head->size = 1;
        head->value = number;
        all_nodes.push_back(head);
        continue;
      }
      head = Insert(head, number);
    }
    if (query == "delete") {
      head = Erase(head, number);
      continue;
    }
    if (query == "exists") {
      if (Exist(head, number)) {
        std::cout << "true\n";
      } else {
        std::cout << "false\n";
      }
    }
    if (query == "next") {
      Next(head, number);
    }
    if (query == "prev") {
      Prev(head, number);
    }
    if (query == "kth") {
      Kth(head, number);
    }
  }
  for (size_t i = 0; i < all_nodes.size(); ++i) {
    delete all_nodes[i];
  }
}
