// В задаче необходимо отсортировать массив поразрядной сортировкой по байтам

#include <iostream>
#include <vector>

int ByteOfNumber(unsigned long long number, size_t byte) {
  const int kBit = 256;
  const int kByte = 8;
  return (number >> (byte * kByte)) & (kBit - 1);
}

void LSDSort(std::vector<unsigned long long>& array) {
  const int kBit = 256;
  const int kByte = 8;
  for (size_t i = 0; i < kByte; ++i) {
    std::vector<unsigned long long> vector_byte(kBit, 0);
    std::vector<unsigned long long> new_array(array.size(), 0);
    std::vector<unsigned long long> array_byte(array.size(), 0);
    for (size_t j = 0; j < array.size(); ++j) {
      array_byte[j] = ByteOfNumber(array[j], i);
      ++vector_byte[array_byte[j]];
    }
    for (size_t j = 1; j < kBit; ++j) {
      vector_byte[j] += vector_byte[j - 1];
    }
    for (int j = array.size() - 1; j >= 0; --j) {
      new_array[vector_byte[array_byte[j]] - 1] = array[j];
      --vector_byte[array_byte[j]];
    }
    array = new_array;
  }
}

int main() {
  size_t array_length;
  std::cin >> array_length;
  std::vector<unsigned long long> array(array_length);
  for (size_t i = 0; i < array_length; ++i) {
    std::cin >> array[i];
  }
  LSDSort(array);
  for (size_t i = 0; i < array_length; ++i) {
    std::cout << array[i] << "\n";
  }
  return 0;
}
