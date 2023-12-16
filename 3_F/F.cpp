// В задаче необходимо реализовать структуру, которая умеет находить
// количество чисел на позициях с x по y по величине в интервале от k до l

#include <algorithm>
#include <iostream>
#include <vector>

class Tree {
 private:
  std::vector<std::vector<int>> tree_;
  std::vector<int> first_;

  static std::vector<int> Merge(std::vector<int>& left_a,
                                std::vector<int>& right_a) {
    std::vector<int> sum_a(left_a.size() + right_a.size());
    size_t i_a = 0;
    size_t j_a = 0;

    while (i_a < left_a.size() || j_a < right_a.size()) {
      if (j_a == right_a.size() ||
          (i_a < left_a.size() && left_a[i_a] <= right_a[j_a])) {
        sum_a[i_a + j_a] = left_a[i_a];
        ++i_a;
      } else {
        sum_a[i_a + j_a] = right_a[j_a];
        ++j_a;
      }
    }
    return sum_a;
  }

  void NewTree(size_t node, int start, int finish) {
    if (start == finish) {
      tree_[node] = {first_[start]};
      return;
    }
    int middle = (start + finish) / 2;
    NewTree(node * 2, start, middle);
    NewTree(node * 2 + 1, middle + 1, finish);
    tree_[node] = Merge(tree_[node * 2], tree_[node * 2 + 1]);
  }

 public:
  Tree(size_t size) {
    first_.resize(size);
    tree_.resize(4 * size);
    for (size_t i = 0; i < size; ++i) {
      std::cin >> first_[i];
    }
    NewTree(1, 0, size - 1);
  }
  long long GetMax(size_t node, std::pair<int, int> start_finish, int left,
                   int right, std::pair<int, int> borders) {
    int start = start_finish.first;
    int finish = start_finish.second;

    if (borders.first > tree_[node][tree_[node].size() - 1] or
        borders.second < tree_[node][0]) {
      return 0;
    }
    if (start == left && finish == right) {
      long long index_start =
          std::lower_bound(tree_[node].begin(), tree_[node].end(),
                           borders.first) -
          tree_[node].begin();
      long long index_finish =
          std::upper_bound(tree_[node].begin(), tree_[node].end(),
                           borders.second) -
          tree_[node].begin();
      return index_finish - index_start;
    }

    std::pair<int, int> new_start_finish;
    int middle = (start + finish) / 2;
    long long result = 0;

    if (left <= middle) {
      new_start_finish.first = start;
      new_start_finish.second = middle;
      result += GetMax(2 * node, new_start_finish, left,
                       std::min(right, middle), borders);
    }
    if (right > middle) {
      new_start_finish.first = middle + 1;
      new_start_finish.second = finish;
      result += GetMax(2 * node + 1, new_start_finish,
                       std::max(left, middle + 1), right, borders);
    }
    return result;
  }
};

void BoostIO() {
  std::ios::sync_with_stdio(false);
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
}

int main() {
  BoostIO();
  size_t count;
  size_t count_query;
  std::cin >> count >> count_query;

  Tree tree(count);
  for (size_t i = 0; i < count_query; ++i) {
    int left;
    int right;
    std::cin >> left >> right;
    std::pair<int, int> borders;
    std::cin >> borders.first >> borders.second;
    std::cout << tree.GetMax(1, {0, count - 1}, left - 1, right - 1, borders)
              << "\n";
  }
}
