// В задаче необходимо вывести k-порядковую статистику

#include <iostream>
#include <random>
#include <vector>

std::pair<size_t, size_t> Partition(std::vector<int>& list, size_t begin,
                                    size_t end) {
  std::mt19937 choose_pivot(time(nullptr));
  size_t index_equals = begin;
  size_t index_larger = begin;
  int pivot = list[begin + choose_pivot() % (end - begin)];

  for (size_t i = begin; i < end; ++i) {
    if (list[i] < pivot) {
      std::swap(list[i], list[index_equals]);
      if (index_equals != index_larger) {
        std::swap(list[i], list[index_larger]);
      }
      ++index_equals;
      ++index_larger;
    } else if (list[i] == pivot) {
      std::swap(list[i], list[index_larger]);
      ++index_larger;
    }
  }
  return {index_equals, index_larger};
}

int QuickSelect(std::vector<int>& list, size_t begin, size_t end,
                size_t statistic) {
  if (begin + 1 >= end) {
    return list[begin];
  }
  auto [index_equals, index_larger] = Partition(list, begin, end);
  if (statistic < index_equals) {
    return QuickSelect(list, begin, index_equals, statistic);
  }
  if (statistic < index_larger) {
    return list[index_equals];
  }
  return QuickSelect(list, index_larger, end, statistic);
}

int main() {
  const int kElem = 2;
  const int kNum123 = 123;
  const int kNum45 = 45;
  const int kNum1e7 = 1e7 + 4321;
  size_t list_length;
  size_t statistic;
  std::cin >> list_length >> statistic;
  std::vector<int> first_list(list_length);
  for (size_t i = 0; i < list_length; ++i) {
    if (i < kElem) {
      std::cin >> first_list[i];
    } else {
      first_list[i] =
          (first_list[i - 1] * kNum123 + first_list[i - 2] * kNum45) % kNum1e7;
    }
  }
  std::cout << QuickSelect(first_list, 0, first_list.size(), statistic - 1);
  return 0;
}
