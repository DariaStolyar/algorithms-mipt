#include <iostream>
#include <string>
#include <vector>

struct Heaps {
  std::vector<long long> min_heap;
  std::vector<long long> max_heap;
  long long last_index_of_heap = 0;
  std::vector<long long> max_to_min;
  std::vector<long long> min_to_max;
  void MinSiftUp(long long index_element) {
    if (index_element == 1) {
      return;
    }
    long long parent = index_element / 2;
    if (min_heap[index_element] < min_heap[parent]) {
      std::swap(min_heap[index_element], min_heap[parent]);
      std::swap(min_to_max[index_element], min_to_max[parent]);
      max_to_min[min_to_max[parent]] = parent;
      max_to_min[min_to_max[index_element]] = index_element;
      MinSiftUp(parent);
    }
  }

  void MaxSiftUp(long long index_element) {
    if (index_element == 1) {
      return;
    }
    long long parent = index_element / 2;
    if (max_heap[index_element] > max_heap[parent]) {
      std::swap(max_heap[index_element], max_heap[parent]);
      std::swap(max_to_min[index_element], max_to_min[parent]);
      min_to_max[max_to_min[parent]] = parent;
      min_to_max[max_to_min[index_element]] = index_element;
      MaxSiftUp(parent);
    }
  }

  void MinSiftDown(long long index_element) {
    if (2 * index_element > last_index_of_heap) {
      return;
    }
    long long last_element = last_index_of_heap;
    long long child = 2 * index_element;
    if (child + 1 <= last_element && min_heap[child + 1] < min_heap[child]) {
      child += 1;
    }
    if (min_heap[child] < min_heap[index_element]) {
      std::swap(min_heap[index_element], min_heap[child]);
      std::swap(min_to_max[index_element], min_to_max[child]);
      max_to_min[min_to_max[child]] = child;
      max_to_min[min_to_max[index_element]] = index_element;
      MinSiftDown(child);
    }
  }

  void MaxSiftDown(long long index_element) {
    if (2 * index_element > last_index_of_heap) {
      return;
    }
    long long last_element = last_index_of_heap;
    long long child = 2 * index_element;
    if (child + 1 <= last_element && max_heap[child + 1] > max_heap[child]) {
      child += 1;
    }
    if (max_heap[child] > max_heap[index_element]) {
      std::swap(max_heap[index_element], max_heap[child]);
      std::swap(max_to_min[index_element], max_to_min[child]);
      min_to_max[max_to_min[child]] = child;
      min_to_max[max_to_min[index_element]] = index_element;
      MaxSiftDown(child);
    }
  }

  void Insert(long long new_element) {
    min_heap.push_back(new_element);
    max_heap.push_back(new_element);
    last_index_of_heap += 1;
    min_to_max[last_index_of_heap] = last_index_of_heap;
    max_to_min[last_index_of_heap] = last_index_of_heap;
    MinSiftUp(last_index_of_heap);
    MaxSiftUp(last_index_of_heap);
  }

  void ExtractMin() {
    long long last = last_index_of_heap;
    size_t first = 1;
    int index_in_max = min_to_max[1];
    std::swap(min_heap[first], min_heap[last]);
    std::swap(min_to_max[first], min_to_max[last]);
    max_to_min[min_to_max[last]] = last;
    max_to_min[min_to_max[first]] = first;
    min_heap.pop_back();
    std::swap(max_heap[index_in_max], max_heap[last]);
    std::swap(max_to_min[index_in_max], max_to_min[last]);
    min_to_max[max_to_min[last]] = last;
    min_to_max[max_to_min[index_in_max]] = index_in_max;
    max_heap.pop_back();
    last_index_of_heap -= 1;
    MinSiftDown(first);
    MaxSiftUp(index_in_max);
  }

  void ExtractMax() {
    long long last = last_index_of_heap;
    size_t first = 1;
    int index_in_min = max_to_min[1];
    std::swap(max_heap[first], max_heap[last]);
    std::swap(max_to_min[first], max_to_min[last]);
    min_to_max[max_to_min[last]] = last;
    min_to_max[max_to_min[first]] = first;
    max_heap.pop_back();
    std::swap(min_heap[index_in_min], min_heap[last]);
    std::swap(min_to_max[index_in_min], min_to_max[last]);
    max_to_min[min_to_max[last]] = last;
    max_to_min[min_to_max[index_in_min]] = index_in_min;
    min_heap.pop_back();
    last_index_of_heap -= 1;
    MaxSiftDown(first);
    MinSiftUp(index_in_min);
  }

  void Clear() {
    std::cout << "ok"
              << "\n";
    for (int i = 0; i < last_index_of_heap; ++i) {
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

void Speed() {
  std::ios::sync_with_stdio(false);
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
}

int main() {
  Speed();
  const int kNumber = 10e6;
  size_t count_query;
  std::cin >> count_query;
  Heaps heaps;
  heaps.max_to_min.resize(kNumber + 1, 0);
  heaps.min_to_max.resize(kNumber + 1, 0);
  heaps.min_heap.push_back(0);
  heaps.max_heap.push_back(0);
  for (size_t i = 0; i < count_query; ++i) {
    heaps.Query();
  }
  return 0;
}
