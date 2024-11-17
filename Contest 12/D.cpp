#include <algorithm>
#include <climits>
#include <iostream>
#include <map>
#include <queue>
#include <valarray>
#include <vector>

void PrepareIO() {
  std::ios::sync_with_stdio(false);
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

long long BinPow(long long number, long long degree, long long module) {
  if (degree == 0) {
    return 1;
  }
  if (degree % 2 == 0) {
    long long halfdegree = BinPow(number, degree / 2, module);
    return (halfdegree * halfdegree) % module;
  }
  return (number * BinPow(number, degree - 1, module)) % module;
}

int Logarithm(int number, int base, int module) {
  const int cNum = (int)std::sqrt(module);
  std::vector<std::pair<int, int>> values1;
  std::vector<std::pair<int, int>> values2;
  for (int i = 1; i < ((module + cNum - 1) / cNum); ++i) {
    values1.push_back({BinPow(base, i * cNum, module), i});
  }
  for (int i = 0; i <= cNum; ++i) {
    values2.push_back({(number * BinPow(base, i, module)) % module, i});
  }
  std::sort(values1.begin(), values1.end());
  std::sort(values2.begin(), values2.end());
  size_t index1 = 0;
  size_t index2 = 0;
  int min_degree = INT_MAX;
  while (index1 != values1.size() and index2 != values2.size()) {
    if (values1[index1].first > values2[index2].first) {
      index2++;
    } else if (values1[index1].first < values2[index2].first) {
      index1++;
    } else {
      min_degree = std::min(
          min_degree, cNum * values1[index1].second - values2[index2].second);
      ++index1;
    }
  }
  if (number == 1) {
    min_degree = 0;
  }
  if (min_degree == INT_MAX) {
    return -1;
  }
  return min_degree;
}

int main() {
  PrepareIO();
  int module;
  int base;
  int number;
  while (std::cin >> module >> base >> number) {
    int log = Logarithm(number, base, module);
    if (log == -1) {
      std::cout << "no solution"
                << "\n";
    } else {
      std::cout << log << "\n";
    }
  }
}
