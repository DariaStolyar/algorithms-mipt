// В задаче необходимо отвечать на запросы второй порядковой статистики
// на отрезках
#include <algorithm>
#include <iostream>
#include <vector>

const int kMaxNumber = static_cast<const int>(1e5 + 3);
const int kMaxDegree = 25;
std::vector<std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>>
    sparse(kMaxDegree,
           std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>(
               kMaxNumber));
std::vector<int> array(kMaxNumber);
std::vector<int> degree(kMaxNumber);

void Build(int size) {
  for (int i = 0; i < size; ++i) {
    sparse[0][i] = {{array[i], i}, {kMaxNumber, kMaxNumber}};
  }
  for (int i = 0; i < size - 1; ++i) {
    if (array[i] < array[i + 1]) {
      sparse[1][i] = {{array[i], i}, {array[i + 1], i + 1}};
    } else {
      sparse[1][i] = {{array[i + 1], i + 1}, {array[i], i}};
    }
  }
  int two = 2;
  for (int i = 2; i < kMaxDegree; ++i) {
    for (int j = 0; j < size - two; ++j) {
      std::vector<std::pair<int, int>> find_small = {
          sparse[i - 1][j].first, sparse[i - 1][j].second,
          sparse[i - 1][j + two].first, sparse[i - 1][j + two].second};
      std::sort(find_small.begin(), find_small.end());
      sparse[i][j] = {find_small[0], find_small[1]};
    }
    two *= 2;
  }
}

int FindNumber(int start, int finish) {
  int index = degree[finish - start + 1];
  std::vector<std::pair<int, int>> find_small = {
      sparse[index][start].first, sparse[index][start].second,
      sparse[index][finish - (1 << index) + 1].first,
      sparse[index][finish - (1 << index) + 1].second};
  std::sort(find_small.begin(), find_small.end());
  if (find_small[0].second == find_small[1].second) {
    return find_small[2].first;
  }
  return find_small[1].first;
}

int main() {
  size_t size;
  size_t count_query;
  std::cin >> size >> count_query;
  for (size_t i = 0; i < size; ++i) {
    std::cin >> array[i];
  }
  Build(static_cast<int>(size));
  int two_degree = 1;
  int degree_i = 0;
  for (int i = 0; i < static_cast<int>(degree.size()); ++i) {
    degree[i] = degree_i;
    if (i == two_degree * 2) {
      two_degree *= 2;
      ++degree_i;
    }
  }
  for (size_t i = 0; i < count_query; ++i) {
    int start;
    int finish;
    std::cin >> start >> finish;
    --start;
    --finish;
    std::cout << FindNumber(start, finish) << "\n";
  }
}
