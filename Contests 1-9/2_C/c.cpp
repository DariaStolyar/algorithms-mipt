#include <deque>
#include <iostream>
#include <string>

void Correction(std::deque<int>& first_half, std::deque<int>& second_half) {
  if (first_half.size() < second_half.size()) {
    first_half.push_back(second_half.front());
    second_half.pop_front();
  }
}

int main() {
  size_t count_query;
  std::cin >> count_query;
  std::deque<int> first_half;
  std::deque<int> second_half;
  for (size_t i = 0; i < count_query; ++i) {
    char type_query;
    std::cin >> type_query;
    if (type_query == '-') {
      std::cout << first_half.front() << "\n";
      first_half.pop_front();
      Correction(first_half, second_half);
    } else {
      int goblin;
      std::cin >> goblin;
      if (type_query == '+') {
        second_half.push_back(goblin);
      } else {
        second_half.push_front(goblin);
      }
      Correction(first_half, second_half);
    }
  }
  return 0;
}

