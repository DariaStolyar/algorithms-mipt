// В задаче необходимо написать очередь с поддержкой минимума

#include <iostream>
#include <stack>
#include <string>

class Hat {
 private:
  std::stack<int> begin_queue_;
  std::stack<int> end_queue_;
  std::stack<int> end_queue_min_;
  std::stack<int> begin_queue_min_;

  void Correction() {
    while (!end_queue_.empty()) {
      begin_queue_.push(end_queue_.top());
      if (begin_queue_min_.empty()) {
        begin_queue_min_.push(end_queue_.top());
      } else {
        begin_queue_min_.push(
            std::min(begin_queue_min_.top(), end_queue_.top()));
      }
      end_queue_.pop();
      end_queue_min_.pop();
    }
  }

 public:
  bool HaveFront() { return !(end_queue_.empty() && begin_queue_.empty()); }

  int Front() {
    if (begin_queue_.empty()) {
      Correction();
    }
    return begin_queue_.top();
  }

  int Min() {
    if (end_queue_min_.empty()) {
      return begin_queue_min_.top();
    }
    if (begin_queue_min_.empty()) {
      return end_queue_min_.top();
    }
    return std::min(begin_queue_min_.top(), end_queue_min_.top());
  }

  void ClearHat() {
    size_t size_begin = begin_queue_.size();
    size_t size_end = end_queue_.size();
    for (size_t j = 0; j < size_begin; ++j) {
      begin_queue_.pop();
      begin_queue_min_.pop();
    }
    for (size_t j = 0; j < size_end; ++j) {
      end_queue_.pop();
      end_queue_min_.pop();
    }
  }

  void Enqueue(int new_element) {
    end_queue_.push(new_element);
    if (end_queue_min_.empty()) {
      end_queue_min_.push(new_element);
    } else {
      end_queue_min_.push(std::min(end_queue_min_.top(), new_element));
    }
  }

  size_t Size() { return begin_queue_.size() + end_queue_.size(); }

  void Dequeue() {
    begin_queue_.pop();
    begin_queue_min_.pop();
  }
};

int main() {
  size_t count_query;
  std::cin >> count_query;
  Hat hat;

  for (size_t i = 0; i < count_query; ++i) {
    std::string type_query;
    std::cin >> type_query;

    if (type_query == "enqueue") {
      int new_element;
      std::cin >> new_element;
      hat.Enqueue(new_element);
      std::cout << "ok"
                << "\n";
    }

    if (type_query == "front") {
      if (hat.HaveFront()) {
        std::cout << hat.Front() << "\n";
      } else {
        std::cout << "error\n";
      }
    }

    if (type_query == "dequeue") {
      if (hat.HaveFront()) {
        std::cout << hat.Front() << "\n";
        hat.Dequeue();
      } else {
        std::cout << "error\n";
      }
    }

    if (type_query == "size") {
      std::cout << hat.Size() << "\n";
    }

    if (type_query == "clear") {
      hat.ClearHat();
      std::cout << "ok\n";
    }

    if (type_query == "min") {
      if (hat.HaveFront()) {
        std::cout << hat.Min() << "\n";
      } else {
        std::cout << "error\n";
      }
    }
  }
}
