// В задаче необходимо вывести k-порядковую статистику

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

int QuickSelect(std::vector<int>& first_list, size_t start, size_t finish,
                size_t stat) {
  if (start + 1 >= finish) {
    return first_list[start];
  }
  std::pair<size_t, size_t> ind_same_and_ind_more;
  ind_same_and_ind_more = Partition(first_list, start, finish);
  size_t ind_same;
  size_t ind_more;
  ind_same = ind_same_and_ind_more.first;
  ind_more = ind_same_and_ind_more.second;
  if (stat < ind_same) {
    return QuickSelect(first_list, start, ind_same, stat);
  }
  if (stat < ind_more) {
    return first_list[ind_same];
  }
  return QuickSelect(first_list, ind_more, finish, stat);
}

int main() {
  const int kElem = 2;
  const int kNum123 = 123;
  const int kNum45 = 45;
  const int kNum1e7 = 1e7 + 4321;
  size_t cnt_elem_list;
  size_t ord_stat;
  std::cin >> cnt_elem_list >> ord_stat;
  std::vector<int> first_list(cnt_elem_list);
  for (size_t i = 0; i < cnt_elem_list; ++i) {
    if (i < kElem) {
      std::cin >> first_list[i];
    } else {
      first_list[i] =
          (first_list[i - 1] * kNum123 + first_list[i - 2] * kNum45) % kNum1e7;
    }
  }
  std::cout << QuickSelect(first_list, 0, first_list.size(), ord_stat - 1);
  return 0;
}
