// В задаче неободимо найти количество раскрасок в 2 цвета поля,
// чтобы в квадратах 2*2 было поровну клеток этих цветов, и с учетом
// начального шаблона

// dp[i][j] - количество раскрасок первых i столбцов, j - маска
// последнего столбца

#include <algorithm>
#include <iostream>
#include <vector>

void BoostIO() {
  std::ios::sync_with_stdio(false);
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

void CreateCheckSample(std::vector<std::vector<int>>& check_sample,
                       std::vector<std::vector<int>> sample, int size1,
                       int size2) {
  for (int j = 0; j < size2; ++j) {
    for (int mask = 0; mask < (1 << size1); ++mask) {
      bool match_sample = true;
      for (int i = 0; i < size1; ++i) {
        if (sample[i][j] == 1 and (mask & (1 << i)) == 0) {
          match_sample = false;
          break;
        }
        if (sample[i][j] == -1 and (mask & (1 << i)) != 0) {
          match_sample = false;
          break;
        }
      }
      if (match_sample) {
        check_sample[j][mask] = 1;
      }
    }
  }
}

void CreateMatchMask(std::vector<std::vector<int>>& match_mask, int size1) {
  for (int mask = 0; mask < (1 << size1); ++mask) {
    bool chered = true;
    int number = 0;
    if ((mask & 1) != 0) {
      number = 1;
    } else {
      number = 0;
    }
    for (int i = 1; i < size1; ++i) {
      if (number == 1 and (mask & (1 << i)) == 0) {
        number = 0;
      } else if (number == 0 and (mask & (1 << i)) != 0) {
        number = 1;
      } else {
        chered = false;
      }
    }
    if (chered) {
      match_mask[mask].push_back(mask);
    }
    match_mask[mask].push_back((1 << size1) - 1 - mask);
  }
}

void FindCountOfColoring(int size1, int size2,
                         std::vector<std::vector<int>> sample) {
  const long long kCountMax = 1e9 + 7;

  std::vector<std::vector<int>> check_sample(size2,
                                             std::vector<int>(1 << size1));
  CreateCheckSample(check_sample, sample, size1, size2);

  std::vector<std::vector<int>> match_mask(1 << size1);
  CreateMatchMask(match_mask, size1);

  std::vector<std::vector<long long>> dp(size2 + 1,
                                         std::vector<long long>(1 << size1));
  for (size_t i = 0; i < check_sample[0].size(); ++i) {
    if (check_sample[0][i] == 1) {
      dp[1][i] = 1;
    }
  }
  long long ans = 0;
  for (int j = 2; j < size2 + 1; ++j) {
    for (int mask = 0; mask < (1 << size1); ++mask) {
      if (check_sample[j - 1][mask] == 1) {
        for (size_t i = 0; i < match_mask[mask].size(); ++i) {
          dp[j][mask] += dp[j - 1][match_mask[mask][i]];
          dp[j][mask] %= kCountMax;
        }
      }
      if (j == size2) {
        ans += dp[j][mask];
        ans %= kCountMax;
      }
    }
  }
  std::cout << ans;
}

int main() {
  BoostIO();
  int size1;
  int size2;
  std::cin >> size1 >> size2;
  std::vector<std::vector<int>> sample(size1, std::vector<int>(size2));
  char symbol;
  for (int i = 0; i < size1; ++i) {
    for (int j = 0; j < size2; ++j) {
      std::cin >> symbol;
      if (symbol == '.') {
        sample[i][j] = 0;
      } else if (symbol == '+') {
        sample[i][j] = 1;
      } else {
        sample[i][j] = -1;
      }
    }
  }
  FindCountOfColoring(size1, size2, sample);
}
