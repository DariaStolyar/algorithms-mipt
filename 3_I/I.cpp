// В задаче необходимо отвечать на запросы второй порядковой статистики
// на отрезке
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

class SparseTable {
 public:
  SparseTable(const std::vector<int>& array);

  void Build();
  int FindNumber(size_t start, size_t finish);

  ~SparseTable() = default;

 private:
  std::vector<std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>>
      sparse_;
  std::vector<int> array_;
  std::vector<size_t> degree_;
  const size_t kMaxDegree;
  void Preprocessing();
};

SparseTable::SparseTable(const std::vector<int>& array)
    : array_(array), kMaxDegree(std::ceil(std::log2(array.size()))) {
  degree_.resize(array_.size() + 1);
  sparse_.resize(
      kMaxDegree + 1,
      std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>(
          array_.size()));
  Preprocessing();
  Build();
}

void SparseTable::Build() {
  for (size_t i = 0; i < array_.size(); ++i) {
    sparse_[0][i] = {{array_[i], i}, {std::numeric_limits<int>::max(), 0}};
  }
  for (size_t i = 0; i < array_.size() - 1; ++i) {
    if (array_[i] < array_[i + 1]) {
      sparse_[1][i] = {{array_[i], i}, {array_[i + 1], i + 1}};
    } else {
      sparse_[1][i] = {{array_[i + 1], i + 1}, {array_[i], i}};
    }
  }

  size_t two_degree = 2;
  for (size_t i = 2; i < kMaxDegree + 1; ++i) {
    for (size_t j = 0; j < array_.size() - two_degree; ++j) {
      std::vector<std::pair<int, int>> find_small = {
          sparse_[i - 1][j].first, sparse_[i - 1][j].second,
          sparse_[i - 1][j + two_degree].first,
          sparse_[i - 1][j + two_degree].second};
      std::sort(find_small.begin(), find_small.end());
      sparse_[i][j] = {find_small[0], find_small[1]};
    }
    two_degree *= 2;
  }
}

int SparseTable::FindNumber(size_t start, size_t finish) {
  size_t index = degree_[finish - start + 1];
  std::vector<std::pair<int, int>> find_small = {
      sparse_[index][start].first, sparse_[index][start].second,
      sparse_[index][finish - (1 << index) + 1].first,
      sparse_[index][finish - (1 << index) + 1].second};
  std::sort(find_small.begin(), find_small.end());
  if (find_small[0].second == find_small[1].second) {
    return find_small[2].first;
  }
  return find_small[1].first;
}

void SparseTable::Preprocessing() {
  size_t two_degree = 1;
  size_t degree_i = 0;
  for (size_t i = 0; i < degree_.size(); ++i) {
    degree_[i] = degree_i;
    if (i == two_degree * 2) {
      two_degree *= 2;
      ++degree_i;
    }
  }
}

int main() {
  size_t size;
  size_t count_query;
  std::cin >> size >> count_query;
  std::vector<int> array;
  array.resize(size);
  for (size_t i = 0; i < size; ++i) {
    std::cin >> array[i];
  }
  SparseTable sparse_table(array);
  for (size_t i = 0; i < count_query; ++i) {
    size_t start;
    size_t finish;
    std::cin >> start >> finish;
    std::cout << sparse_table.FindNumber(start - 1, finish - 1) << "\n";
  }
}
