// В задаче необходимо реализовать AVL-дерево

#include <algorithm>
#include <iostream>
#include <optional>
#include <random>
#include <string>
#include <vector>

struct Node {
  int key = 0;
  size_t heigth = 0;
  Node* left_son = nullptr;
  Node* right_son = nullptr;
};

class AVL {
 public:
  AVL() = default;
  void Add(int new_element);
  std::optional<int> Next(int value);
  ~AVL();

 private:
  Node* head_ = nullptr;
  std::vector<Node*> all_nodes_;
  static void ChangeHeight(Node* node);
  static int GetHeight(Node* node);
  static int GetHeightDifference(Node* node);

  static Node* SmallLeftChange(Node* node);
  static Node* SmallRightChange(Node* node);
  static Node* BigLeftChange(Node* node);
  static Node* BigRightChange(Node* node);

  bool Exist(int element) const;
  Node* Addition(Node* node, int new_element);
};

void AVL::Add(int new_element) {
  if (Exist(new_element)) {
    return;
  }
  head_ = Addition(head_, new_element);
}

std::optional<int> AVL::Next(int value) {
  if (Exist(value)) {
    return value;
  }
  Node* node = head_;
  std::optional<int> normal_value = std::nullopt;
  while (node != nullptr) {
    if (node->key <= value) {
      node = node->right_son;
      continue;
    }
    if (!normal_value) {
      normal_value = node->key;
    }
    normal_value.value() = std::min(node->key, normal_value.value());
    node = node->left_son;
  }
  if (normal_value) {
    return normal_value;
  }
  return {};
}

AVL::~AVL() {
  for (auto* node : all_nodes_) {
    delete node;
  }
}

void AVL::ChangeHeight(Node* node) {
  size_t heigth_left = (node->left_son != nullptr ? node->left_son->heigth : 0);
  size_t heigth_right =
      (node->right_son != nullptr ? node->right_son->heigth : 0);
  node->heigth = 1 + std::max(heigth_left, heigth_right);
}

int AVL::GetHeight(Node* node) {
  if (node == nullptr) {
    return 0;
  }
  ChangeHeight(node);
  return node->heigth;
}

int AVL::GetHeightDifference(Node* node) {
  if (node == nullptr) {
    return 0;
  }
  return GetHeight(node->left_son) - GetHeight(node->right_son);
}

Node* AVL::SmallLeftChange(Node* node) {
  Node* son = node->right_son;
  node->right_son = son->left_son;
  son->left_son = node;
  ChangeHeight(node);
  ChangeHeight(son);
  return son;
}

Node* AVL::SmallRightChange(Node* node) {
  Node* son = node->left_son;
  node->left_son = son->right_son;
  son->right_son = node;
  ChangeHeight(node);
  ChangeHeight(son);
  return son;
}

Node* AVL::BigLeftChange(Node* node) {
  node->right_son = SmallRightChange(node->right_son);
  return SmallLeftChange(node);
}

Node* AVL::BigRightChange(Node* node) {
  node->left_son = SmallLeftChange(node->left_son);
  return SmallRightChange(node);
}

bool AVL::Exist(int element) const {
  Node* node = head_;
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

Node* AVL::Addition(Node* node, int new_element) {
  if (node == nullptr) {
    node = new Node;
    node->key = new_element;
    node->heigth = 1;
    all_nodes_.push_back(node);
    return node;
  }

  if (node->key > new_element) {
    node->left_son = Addition(node->left_son, new_element);
  } else {
    node->right_son = Addition(node->right_son, new_element);
  }

  ChangeHeight(node);
  int delta_height = GetHeightDifference(node);
  if (delta_height == -2) {
    if (GetHeightDifference(node->right_son) != 1) {
      node = SmallLeftChange(node);
    } else {
      node = BigLeftChange(node);
    }
  }

  if (delta_height == 2) {
    if (GetHeightDifference(node->left_son) != -1) {
      node = SmallRightChange(node);
    } else {
      node = BigRightChange(node);
    }
  }
  ChangeHeight(node);

  return node;
}

void BoostIO() {
  std::ios::sync_with_stdio(false);
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

int main() {
  BoostIO();

  const int kMax = 1e9;
  size_t count_query;
  std::cin >> count_query;
  long long last_query = 0;
  AVL avl;

  for (size_t i = 0; i < count_query; ++i) {
    std::string query;
    std::cin >> query;
    if (query == "+") {
      int number;
      std::cin >> number;
      avl.Add((number + last_query) % kMax);
      last_query = 0;
    } else {
      int car;
      std::cin >> car;
      std::optional<int> next = avl.Next(car);
      if (next) {
        std::cout << next.value() << "\n";
        last_query = next.value();
      } else {
        std::cout << "-1\n";
        last_query = -1;
      }
    }
  }
}
