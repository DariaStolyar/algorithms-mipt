// В задаче необходимо написать очередь с поддержкой минимума

#include <iostream>
#include <stack>
#include <string>

struct Hat {
  const int kMinValue = -1e9;
  std::stack<int> begin_queue;
  std::stack<int> end_queue;
  std::stack<int> end_queue_min;
  std::stack<int> begin_queue_min;

  void Correction() {
    while (!end_queue.empty()) {
      begin_queue.push(end_queue.top());
      if (begin_queue_min.empty()) {
        begin_queue_min.push(end_queue.top());
      } else {
        begin_queue_min.push(std::min(begin_queue_min.top(), end_queue.top()));
      }
      end_queue.pop();
      end_queue_min.pop();
    }
  }

  int Front() {
    if (end_queue.empty() && begin_queue.empty()) {
      return kMinValue;
    }
    if (begin_queue.empty()) {
      Correction();
    }
    return begin_queue.top();
  }

  void PrintMin() {
    if (end_queue_min.empty() && begin_queue_min.empty()) {
      std::cout << "error"
                << "\n";
    } else if (end_queue_min.empty()) {
      std::cout << begin_queue_min.top() << "\n";
    } else if (begin_queue_min.empty()) {
      std::cout << end_queue_min.top() << "\n";
    } else {
      std::cout << std::min(begin_queue_min.top(), end_queue_min.top()) << "\n";
    }
  }

  void ClearHat() {
    size_t size_begin = begin_queue.size();
    size_t size_end = end_queue.size();
    for (size_t j = 0; j < size_begin; ++j) {
      begin_queue.pop();
      begin_queue_min.pop();
    }
    for (size_t j = 0; j < size_end; ++j) {
      end_queue.pop();
      end_queue_min.pop();
    }
    std::cout << "ok"
              << "\n";
  }
};

int main() {
  const int kMinValue = -1e9;
  size_t count_query;
  std::cin >> count_query;
  Hat hat;

  for (size_t i = 0; i < count_query; ++i) {
    std::string type_query;
    std::cin >> type_query;

    if (type_query == "enqueue") {
      int new_element;
      std::cin >> new_element;
      hat.end_queue.push(new_element);
      if (hat.end_queue_min.empty()) {
        hat.end_queue_min.push(new_element);
      } else {
        hat.end_queue_min.push(std::min(hat.end_queue_min.top(), new_element));
      }
      std::cout << "ok"
                << "\n";
    }

    if (type_query == "front") {
      if (hat.Front() != kMinValue) {
        std::cout << hat.Front() << "\n";
      } else {
        std::cout << "error\n";
      }
    }

    if (type_query == "dequeue") {
      if (hat.Front() != kMinValue) {
        std::cout << hat.Front() << "\n";
        hat.begin_queue.pop();
        hat.begin_queue_min.pop();
      } else {
        std::cout << "error\n";
      }
    }

    if (type_query == "size") {
      std::cout << hat.begin_queue.size() + hat.end_queue.size() << "\n";
    }

    if (type_query == "clear") {
      hat.ClearHat();
    }

    if (type_query == "min") {
      hat.PrintMin();
    }
  }
}
