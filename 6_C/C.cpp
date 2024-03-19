// В задаче необходимо вывести минимальное число экспериментов,
// необходимое чтобы определить этаж, начиная с которого ломаются самолеты.

// dp[i][j] - максимальный этаж, который можно узнать при
// i экспериментaх и j самолетиках

#include <algorithm>
#include <climits>
#include <iostream>
#include <string>
#include <vector>

void BoostIO() {
  std::ios::sync_with_stdio(false);
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

int main() {
  BoostIO();

  int height;
  int count;
  std::cin >> height >> count;
  std::vector<int> dp_string_i(count + 1);
  std::vector<int> dp_new_string(count + 1);
  if (1 >= height) {
    std::cout << 0;
    return 0;
  }
  for (int j = 0; j < count + 1; ++j) {
    if (j == 0) {
      dp_string_i[j] = 1;
    } else {
      dp_string_i[j] = 2;
    }
  }
  if (dp_string_i[count] >= height) {
    std::cout << 1;
    return 0;
  }
  for (int i = 2; i <= height; ++i) {
    dp_new_string[0] = 1;
    if (count >= 1) {
      dp_new_string[1] = i + 1;
    }
    for (int j = 2; j < count + 1; ++j) {
      dp_new_string[j] = dp_string_i[j] + dp_string_i[j - 1];
    }
    if (dp_new_string[count] >= height) {
      std::cout << i;
      return 0;
    }
    std::copy(dp_new_string.begin(), dp_new_string.end(), dp_string_i.begin());
  }
  std::cout << -1;
}
