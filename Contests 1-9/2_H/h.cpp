#include <iostream>
#include <string>
#include <vector>

class Heaps {
 public:
  std::vector<long long> min_heap;
  std::vector<long long> max_heap;
  size_t last_index_of_heap = 0;
  std::vector<long long> max_to_min;
  std::vector<long long> min_to_max;
  Heaps() {
    const int kNumber = 10e6;
    max_to_min.resize(kNumber + 1, 0);
    min_to_max.resize(kNumber + 1, 0);
    min_heap.push_back(0);
    max_heap.push_back(0);
  }
  void SwapMin(size_t first_index, size_t second_index) {
    std::swap(min_heap[first_index], min_heap[second_index]);
    std::swap(min_to_max[first_index], min_to_max[second_index]);
    max_to_min[min_to_max[second_index]] = second_index;
    max_to_min[min_to_max[first_index]] = first_index;
  }
  void SwapMax(size_t first_index, size_t second_index) {
    std::swap(max_heap[first_index], max_heap[second_index]);
    std::swap(max_to_min[first_index], max_to_min[second_index]);
    min_to_max[max_to_min[second_index]] = second_index;
    min_to_max[max_to_min[first_index]] = first_index;
  }
  void MinSiftUp(size_t index_element) {
    if (index_element == 1) {
      return;
    }
    long long parent = index_element / 2;
    if (min_heap[index_element] < min_heap[parent]) {
      SwapMin(index_element, parent);
      MinSiftUp(parent);
    }
  }

  void MaxSiftUp(size_t index_element) {
    if (index_element == 1) {
      return;
    }
    size_t parent = index_element / 2;
    if (max_heap[index_element] > max_heap[parent]) {
      SwapMax(index_element, parent);
      MaxSiftUp(parent);
    }
  }

  void MinSiftDown(size_t index_element) {
    if (2 * index_element > last_index_of_heap) {
      return;
    }
    size_t last_element = last_index_of_heap;
    size_t child = 2 * index_element;
    if (child + 1 <= last_element && min_heap[child + 1] < min_heap[child]) {
      ++child;
    }
    if (min_heap[child] < min_heap[index_element]) {
      SwapMin(index_element, child);
      MinSiftDown(child);
    }
  }

  void MaxSiftDown(size_t index_element) {
    if (2 * index_element > last_index_of_heap) {
      return;
    }
    size_t last_element = last_index_of_heap;
    size_t child = 2 * index_element;
    if (child + 1 <= last_element && max_heap[child + 1] > max_heap[child]) {
      ++child;
    }
    if (max_heap[child] > max_heap[index_element]) {
      SwapMax(index_element, child);
      MaxSiftDown(child);
    }
  }

  void Insert(size_t new_element) {
    min_heap.push_back(new_element);
    max_heap.push_back(new_element);
    last_index_of_heap += 1;
    min_to_max[last_index_of_heap] = last_index_of_heap;
    max_to_min[last_index_of_heap] = last_index_of_heap;
    MinSiftUp(last_index_of_heap);
    MaxSiftUp(last_index_of_heap);
  }

  void ExtractMin() {
    size_t last = last_index_of_heap;
    size_t first = 1;
    int index_in_max = min_to_max[1];
    SwapMin(first, last);
    min_heap.pop_back();
    SwapMax(index_in_max, last);
    max_heap.pop_back();
    last_index_of_heap -= 1;
    MinSiftDown(first);
    MaxSiftUp(index_in_max);
  }

  void ExtractMax() {
    size_t last = last_index_of_heap;
    size_t first = 1;
    int index_in_min = max_to_min[1];
    SwapMax(first, last);
    max_heap.pop_back();
    SwapMin(index_in_min, last);
    min_heap.pop_back();
    last_index_of_heap -= 1;
    MaxSiftDown(first);
    MinSiftUp(index_in_min);
  }

  void Clear() {
    std::cout << "ok"
              << "\n";
    for (size_t i = 0; i < last_index_of_heap; ++i) {
      max_heap.pop_back();
      min_heap.pop_back();
      min_to_max[i] = 0;
      max_to_min[i] = 0;
    }
    last_index_of_heap = 0;
  }

  void Query() {
    std::string type_query;
    std::cin >> type_query;
    if (type_query == "get_min") {
      if (last_index_of_heap == 0) {
        std::cout << "error"
                  << "\n";
        return;
      }
      std::cout << min_heap[1] << "\n";
    }
    if (type_query == "get_max") {
      if (last_index_of_heap == 0) {
        std::cout << "error"
                  << "\n";
        return;
      }
      std::cout << max_heap[1] << "\n";
    }
    if (type_query == "insert") {
      int new_element;
      std::cin >> new_element;
      Insert(new_element);
      std::cout << "ok"
                << "\n";
    }
    if (type_query == "extract_min") {
      if (last_index_of_heap == 0) {
        std::cout << "error"
                  << "\n";
        return;
      }
      std::cout << min_heap[1] << "\n";
      ExtractMin();
    }
    if (type_query == "extract_max") {
      if (last_index_of_heap == 0) {
        std::cout << "error"
                  << "\n";
        return;
      }
      std::cout << max_heap[1] << "\n";
      ExtractMax();
    }
    if (type_query == "size") {
      std::cout << last_index_of_heap << "\n";
    }
    if (type_query == "clear") {
      Clear();
    }
  }
};

void BoostIO() {
  std::ios::sync_with_stdio(false);
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
}

int main() {
  BoostIO();
  size_t count_query;
  std::cin >> count_query;
  Heaps heaps;
  for (size_t i = 0; i < count_query; ++i) {
    heaps.Query();
  }
  return 0;
}
