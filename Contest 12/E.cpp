#include <algorithm>
#include <climits>
#include <iostream>
#include <map>
#include <queue>
#include <vector>

void PrepareIO() {
  std::ios::sync_with_stdio(false);
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

long long BinPow(long long number, long long degree, long long module) {
  if (degree == 0) {
    return 1;
  }
  if (degree % 2 == 0) {
    long long halfdegree = BinPow(number, degree / 2, module);
    return (halfdegree * halfdegree) % module;
  }
  return (number * BinPow(number, degree - 1, module)) % module;
}

long long GenerateNotDeduction(long long module) {
  while (true) {
    long long number = rand() % module;
    if (BinPow(number, (module - 1) / 2, module) == module - 1) {
      return number;
    }
  }
}

long long FindOrd(long long number, long long module) {
  long long index = 0;
  while (true) {
    if (number == 1) {
      return index;
    }
    index += 1;
    number = (number * number) % module;
  }
}

long long SquareRoot(long long number, long long module) {
  if (module == 2) {
    return number;
  }
  if (BinPow(number, (module - 1) / 2, module) == module - 1) {
    return -1;
  }
  long long not_deduction = GenerateNotDeduction(module);
  long long odd = module - 1;
  long long count2 = 0;
  while (odd % 2 == 0) {
    odd /= 2;
    count2 += 1;
  }
  std::pair<long long, long long> pair_i = {
      BinPow(number, odd, module), BinPow(number, (odd + 1) / 2, module)};
  if (pair_i.first == 1) {
    return pair_i.second;
  }
  long long auxiliary = BinPow(not_deduction, odd, module);
  while (pair_i.first != 1) {
    long long ord = FindOrd(pair_i.first, module);
    if (count2 - ord < 0) {
      return -1;
    }
    pair_i.first =
        (pair_i.first * BinPow(auxiliary, (1LL << (count2 - ord)), module)) %
        module;
    pair_i.second = (pair_i.second *
                     BinPow(auxiliary, (1LL << (count2 - ord - 1)), module)) %
                    module;
  }
  return pair_i.second;
}

int main() {
  PrepareIO();
  long long count_tests;
  std::cin >> count_tests;
  for (long long test = 0; test < count_tests; ++test) {
    long long prime;
    long long number;
    std::cin >> number >> prime;
    long long root = SquareRoot(number, prime);
    if (root == -1) {
      std::cout << "IMPOSSIBLE"
                << "\n";
    } else {
      std::cout << root << "\n";
    }
  }
}
