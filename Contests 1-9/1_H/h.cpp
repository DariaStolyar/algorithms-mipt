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

void QuickSort(std::vector<int>& list, size_t begin, size_t end) {
  if (begin + 1 < end) {
    auto [index_equals, index_larger] = Partition(list, begin, end);
    QuickSort(list, begin, index_equals);
    QuickSort(list, index_larger, end);
  }
}

int main() {
  size_t list_length;
  std::cin >> list_length;
  std::vector<int> list(list_length);
  for (size_t i = 0; i < list_length; ++i) {
    std::cin >> list[i];
  }

  QuickSort(list, 0, list.size());

  for (size_t i = 0; i < list_length; ++i) {
    std::cout << list[i] << " ";
  }
  return 0;
}
