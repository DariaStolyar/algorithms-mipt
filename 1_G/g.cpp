// В задаче необходимо отсортировать массив поразрядной сортировкой по байтам

#include <iostream>
#include <vector>
#include <numeric>

size_t ByteOfNumber(unsigned long long number, size_t byte) {
  const size_t kBit = 256;
  const size_t kByte = 8;
  return (number >> (byte * kByte)) & (kBit - 1);
}

void LSDSort(std::vector<unsigned long long>& array) {
  const size_t kBit = 256;
  const size_t kByte = 8;
  for (size_t i = 0; i < kByte; ++i) {
    std::vector<unsigned long long> counts_of_numbers(kBit, 0);
    std::vector<unsigned long long> indexes(kBit, 0);
    std::vector<unsigned long long> sorted(array.size(), 0);
    for (size_t j = 0; j < array.size(); ++j) {
      size_t j_byte = ByteOfNumber(array[j], i);
      ++counts_of_numbers[j_byte];
    }
    std::partial_sum(counts_of_numbers.begin(), counts_of_numbers.end(),indexes.begin());
    for (int j = array.size() - 1; j >= 0; --j) {
      size_t j_byte = ByteOfNumber(array[j], i);
      sorted[indexes[j_byte] - 1] = array[j];
      --indexes[j_byte];
    }
    array = sorted;
  }
}

int main() {
  size_t length;
  std::cin >> length;
  std::vector<unsigned long long> array(length);
  for (size_t i = 0; i < length; ++i) {
    std::cin >> array[i];
  }
  LSDSort(array);
  for (size_t i = 0; i < length; ++i) {
    std::cout << array[i] << "\n";
  }
  return 0;
}
