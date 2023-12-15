// В задаче необходимо реализовать кучу на минимум
// с операцией уменьшения числа по номеру запроса

#include <iostream>
#include <string>
#include <vector>

class Heap {
 private:
  std::vector<long long> heap_;
  size_t last_index_ = 0;
  std::vector<size_t> to_queries_;
  std::vector<size_t> queries_;

  void Swap(size_t first_index, size_t second_index) {
    std::swap(heap_[first_index], heap_[second_index]);
    std::swap(to_queries_[first_index], to_queries_[second_index]);
    queries_[to_queries_[second_index]] = second_index;
    queries_[to_queries_[first_index]] = first_index;
  }

  void SiftUp(size_t index_element) {
    if (index_element == 1) {
      return;
    }
    size_t parent = index_element / 2;
    if (heap_[index_element] < heap_[parent]) {
      Swap(index_element, parent);
      SiftUp(parent);
    }
  }

  void SiftDown(size_t index_element) {
    if (2 * index_element > last_index_) {
      return;
    }
    size_t last_element = last_index_;
    size_t child = 2 * index_element;
    if (child + 1 <= last_element && heap_[child + 1] < heap_[child]) {
      child += 1;
    }
    if (heap_[child] < heap_[index_element]) {
      Swap(child, index_element);
      SiftDown(child);
    }
  }

 public:
  Heap(size_t size) {
    queries_.resize(size + 1, 0);
    to_queries_.resize(size + 1, 0);
    heap_.push_back(0);
  }

  void Insert(size_t index_query, long long new_element) {
    heap_.push_back(new_element);
    ++last_index_;
    to_queries_[last_index_] = index_query;
    queries_[index_query] = last_index_;
    SiftUp(last_index_);
  }

  void ExtractMin() {
    size_t last = last_index_;
    size_t first = 1;
    std::swap(heap_[first], heap_[last]);
    std::swap(to_queries_[first], to_queries_[last]);
    queries_[to_queries_[last]] = last;
    queries_[to_queries_[first]] = first;
    heap_.pop_back();
    last_index_ -= 1;
    SiftDown(first);
  }

  void DecreaseKey(size_t index_query, long long delta) {
    size_t index_element = queries_[index_query];
    heap_[index_element] -= delta;
    SiftUp(index_element);
  }

  long long GetMin() { return heap_[1]; }
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
  Heap heap(count_query);
 
  for (size_t i = 0; i < count_query; ++i) {
    std::string type_query;
    std::cin >> type_query;
   
    if (type_query == "getMin") {
      std::cout << heap.GetMin() << "\n";
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
      size_t index_query;
      long long delta;
      std::cin >> index_query >> delta;
      heap.DecreaseKey(index_query, delta);
    }
  }
  return 0;
}
