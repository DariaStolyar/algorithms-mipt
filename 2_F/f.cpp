#include <iostream>
#include <string>
#include <vector>

class Heap {
 public:
  std::vector<long long> binary_heap;
  long long last_index_of_heap = 0;
  std::vector<long long> heap_to_queries;
  std::vector<long long> queries;
  Heap() {
    const int kNumber = 10e6;
    queries.resize(kNumber + 1, 0);
    heap_to_queries.resize(kNumber + 1, 0);
    binary_heap.push_back(0);
  }
  void Swap(long long first_index, long long second_index) {
    std::swap(binary_heap[first_index], binary_heap[second_index]);
    std::swap(heap_to_queries[first_index], heap_to_queries[second_index]);
    queries[heap_to_queries[second_index]] = second_index;
    queries[heap_to_queries[first_index]] = first_index;
  }
  void SiftUp(long long index_element) {
    if (index_element == 1) {
      return;
    }
    long long parent = index_element / 2;
    if (binary_heap[index_element] < binary_heap[parent]) {
      Swap(index_element, parent);
      SiftUp(parent);
    }
  }
  void SiftDown(long long index_element) {
    if (2 * index_element > last_index_of_heap) {
      return;
    }
    long long last_element = last_index_of_heap;
    long long child = 2 * index_element;
    if (child + 1 <= last_element &&
        binary_heap[child + 1] < binary_heap[child]) {
      child += 1;
    }
    if (binary_heap[child] < binary_heap[index_element]) {
      Swap(child, index_element);
      SiftDown(child);
    }
  }
  void Insert(size_t index_query, long long new_element) {
    binary_heap.push_back(new_element);
    ++last_index_of_heap;
    heap_to_queries[last_index_of_heap] = index_query;
    queries[index_query] = last_index_of_heap;
    SiftUp(last_index_of_heap);
  }

  void ExtractMin() {
    long long last = last_index_of_heap;
    size_t first = 1;
    std::swap(binary_heap[first], binary_heap[last]);
    std::swap(heap_to_queries[first], heap_to_queries[last]);
    queries[heap_to_queries[last]] = last;
    queries[heap_to_queries[first]] = first;
    binary_heap.pop_back();
    last_index_of_heap -= 1;
    SiftDown(first);
  }

  void DecreaseKey(long long index_query, long long delta) {
    long long index_element = queries[index_query];
    binary_heap[index_element] -= delta;
    SiftUp(index_element);
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
  Heap heap;
  for (size_t i = 0; i < count_query; ++i) {
    std::string type_query;
    std::cin >> type_query;
    if (type_query == "getMin") {
      std::cout << heap.binary_heap[1] << "\n";
    }
    if (type_query == "insert") {
      int new_element;
      std::cin >> new_element;
      heap.Insert(i + 1, new_element);
    }
    if (type_query == "extractMin") {
      heap.ExtractMin();
    }
    if (type_query == "decreaseKey") {
      long long index_query;
      long long delta;
      std::cin >> index_query >> delta;
      heap.DecreaseKey(index_query, delta);
    }
  }
  return 0;
}
