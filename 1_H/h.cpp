#include <iostream>
#include <random>
#include <vector>

std::mt19937 choose_pivot(time(nullptr));

std::pair<size_t, size_t> Partition(std::vector<int>& first_list, size_t start,
                                    size_t finish) {
  size_t ind_same = start;
  size_t ind_more = start;
  int pivot = first_list[start + choose_pivot() % (finish - start)];
  for (size_t i = start; i < finish; ++i) {
    if (first_list[i] < pivot) {
      std::swap(first_list[i], first_list[ind_same]);
      if (ind_same != ind_more) {
        std::swap(first_list[i], first_list[ind_more]);
      }
      ++ind_same;
      ++ind_more;
    } else if (first_list[i] == pivot) {
      std::swap(first_list[i], first_list[ind_more]);
      ++ind_more;
    }
  }
  return {ind_same, ind_more};
}

void QuickSort(std::vector<int>& first_list, size_t start, size_t finish) {
  if (start + 1 < finish) {
    std::pair<size_t, size_t> ind_same_and_ind_more;
    ind_same_and_ind_more = Partition(first_list, start, finish);
    size_t ind_same;
    size_t ind_more;
    ind_same = ind_same_and_ind_more.first;
    ind_more = ind_same_and_ind_more.second;
    QuickSort(first_list, start, ind_same);
    QuickSort(first_list, ind_more, finish);
  }
}

int main() {
  size_t cnt_elem_list;
  std::cin >> cnt_elem_list;
  std::vector<int> first_list(cnt_elem_list);
  for (size_t i = 0; i < cnt_elem_list; ++i) {
    std::cin >> first_list[i];
  }
  QuickSort(first_list, 0, first_list.size());
  for (size_t i = 0; i < cnt_elem_list; ++i) {
    std::cout << first_list[i] << " ";
  }
  return 0;
}
