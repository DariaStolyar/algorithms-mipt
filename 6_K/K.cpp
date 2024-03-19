// В задаче необходимо реализовать задачу о рюкзаке с восстановлением

// dp[i][j] - максимальная сумма, которую можно заработать, если выполнить
// задания с номерами <= i и потратить ресурса <= j

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

  int count;
  int volume;
  std::cin >> count >> volume;
  std::vector<int> resources(count);
  std::vector<int> money(count);
  for (int i = 0; i < count; ++i) {
    std::cin >> resources[i];
  }
  for (int i = 0; i < count; ++i) {
    std::cin >> money[i];
  }

  std::vector<std::vector<int>> dp(count + 1, std::vector<int>(volume + 1));

  for (int i = 1; i < count + 1; ++i) {
    for (int j = 0; j < volume + 1; ++j) {
      if (j < resources[i - 1]) {
        dp[i][j] = dp[i - 1][j];
        continue;
      }
      dp[i][j] = std::max(dp[i - 1][j],
                          dp[i - 1][j - resources[i - 1]] + money[i - 1]);
    }
  }

  int res_i = count;
  int vol_i = volume;
  while (res_i != 0 and vol_i != 0) {
    if (dp[res_i][vol_i] == dp[res_i - 1][vol_i]) {
      res_i -= 1;
      continue;
    }
    std::cout << res_i << " ";
    vol_i -= resources[res_i - 1];
    res_i -= 1;
  }
}
