// В задаче необходимо найти максимальную невозрастающую
//подпоследовательность

// dp[i] - на какой наибольший элемент может заканчиваться
// последовательность длины i

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

  int force;
  std::cin >> force;
  std::vector<int> vector(force);
  for (int i = 0; i < force; ++i) {
    std::cin >> vector[i];
  }

  std::vector<int> dp(force + 1, INT_MIN);
  std::vector<int> indices(force + 1);
  std::vector<int> parent(force + 1, -1);

  int index = 1;
  dp[0] = vector[0];
  indices[0] = 0;
  parent[0] = -1;

  for (int i = 1; i < force; ++i) {
    if (vector[i] <= dp[index - 1]) {
      dp[index] = vector[i];
      indices[index] = i;
      parent[i] = indices[index - 1];
      index += 1;
    } else {
      int new_position =
          dp.size() -
          (std::lower_bound(dp.rbegin(), dp.rend(), vector[i]) - dp.rbegin());
      dp[new_position] = vector[i];
      indices[new_position] = i;
      if (new_position == 0) {
        parent[i] = -1;
      } else {
        parent[i] = indices[new_position - 1];
      }
    }
  }
  std::vector<int> answer;
  index = indices[index - 1];
  while (index >= 0) {
    answer.push_back(index);
    index = parent[index];
  }
  std::cout << answer.size() << "\n";
  for (int i = answer.size() - 1; i > -1; --i) {
    std::cout << answer[i] + 1 << " ";
  }
}
