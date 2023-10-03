#include <iostream>
#include <vector>

const int kBit = 256;
const int kByte = 8;

int main() {
  size_t cnt_elem_list;
  std::cin >> cnt_elem_list;
  std::vector<unsigned long long> first_list(cnt_elem_list);
  for (size_t i = 0; i < cnt_elem_list; ++i) {
    std::cin >> first_list[i];
  }
  for (size_t i = 0; i < kByte; ++i) {
    std::vector<std::vector<unsigned long long>> list_byte(kBit);
    for (size_t j = 0; j < cnt_elem_list; ++j) {
      int j_byte = ((first_list[j] >> (i * kByte)) & (kBit - 1));
      list_byte[j_byte].push_back(first_list[j]);
    }
    size_t i_in_first_list = 0;
    for (size_t j = 0; j < kBit; ++j) {
      for (size_t i_in_list_byte = 0; i_in_list_byte < list_byte[j].size();
           ++i_in_list_byte) {
        first_list[i_in_first_list] = list_byte[j][i_in_list_byte];
        ++i_in_first_list;
      }
    }
  }
  for (size_t i = 0; i < cnt_elem_list; ++i) {
    std::cout << first_list[i] << "\n";
  }
  return 0;
}
