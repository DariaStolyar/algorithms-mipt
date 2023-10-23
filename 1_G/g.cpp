#include <iostream>
#include <vector>

void Sort(std::vector<unsigned long long>& list) {
  const int kBit = 256;
  const int kByte = 8;
  for (size_t i = 0; i < kByte; ++i) {
    std::vector<std::vector<unsigned long long>> list_byte(kBit);
    for (size_t j = 0; j < list.size(); ++j) {
      int j_byte = ((list[j] >> (i * kByte)) & (kBit - 1));
      list_byte[j_byte].push_back(list[j]);
    }
    size_t i_in_first_list = 0;
    for (size_t j = 0; j < kBit; ++j) {
      for (size_t i_in_list_byte = 0; i_in_list_byte < list_byte[j].size();
           ++i_in_list_byte) {
        list[i_in_first_list] = list_byte[j][i_in_list_byte];
        ++i_in_first_list;
      }
    }
  }
}

int main() {
  size_t list_length;
  std::cin >> list_length;
  std::vector<unsigned long long> list(list_length);
  for (size_t i = 0; i < list_length; ++i) {
    std::cin >> list[i];
  }
  Sort(list);
  for (size_t i = 0; i < list_length; ++i) {
    std::cout << list[i] << "\n";
  }
  return 0;
}
