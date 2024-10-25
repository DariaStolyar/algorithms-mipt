#include <algorithm>
#include <climits>
#include <iostream>
#include <map>
#include <queue>
#include <vector>

const int cCodeZ = 122;

void PrepareIO() {
  std::ios::sync_with_stdio(false);
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

void Sort(std::string& str, std::vector<int>& sort, std::vector<int>& classes) {
  std::vector<int> cnt(cCodeZ + 1, 0);
  for (size_t i = 0; i < str.size(); ++i) {
    ++cnt[str[i]];
  }
  for (size_t i = 1; i < cnt.size(); ++i) {
    cnt[i] += cnt[i - 1];
  }
  for (int i = static_cast<int>(str.size()) - 1; i >= 0; --i) {
    sort[--cnt[str[i]]] = i;
  }
  int number = 0;
  for (size_t i = 0; i < str.size(); ++i) {
    if (i > 0 && str[sort[i]] != str[sort[i - 1]]) {
      ++number;
    }
    classes[sort[i]] = number;
  }
}

void SortPairs(std::vector<std::tuple<int, int, int>>& clas_pair) {
  std::vector<std::tuple<int, int, int>> clas(clas_pair.size());
  for (size_t i = 0; i < clas_pair.size(); ++i) {
    clas[i] = {std::get<0>(clas_pair[i]), std::get<1>(clas_pair[i]),
               std::get<2>(clas_pair[i])};
  }
  std::vector<int> cnt(clas_pair.size(), 0);
  for (size_t i = 0; i < clas_pair.size(); ++i) {
    ++cnt[std::get<1>(clas[i])];
  }
  for (size_t i = 1; i < cnt.size(); ++i) {
    cnt[i] += cnt[i - 1];
  }
  for (int i = static_cast<int>(clas_pair.size()) - 1; i >= 0; --i) {
    clas_pair[--cnt[std::get<1>(clas[i])]] = {
            std::get<0>(clas[i]), std::get<1>(clas[i]), std::get<2>(clas[i])};
  }
  for (size_t i = 0; i < clas_pair.size(); ++i) {
    clas[i] = {std::get<0>(clas_pair[i]), std::get<1>(clas_pair[i]),
               std::get<2>(clas_pair[i])};
  }
  for (size_t i = 0; i < cnt.size(); ++i) {
    cnt[i] = 0;
  }
  for (size_t i = 0; i < clas_pair.size(); ++i) {
    ++cnt[std::get<0>(clas[i])];
  }
  for (size_t i = 1; i < cnt.size(); ++i) {
    cnt[i] += cnt[i - 1];
  }
  for (int i = static_cast<int>(clas_pair.size()) - 1; i >= 0; --i) {
    clas_pair[--cnt[std::get<0>(clas[i])]] = {
            std::get<0>(clas[i]), std::get<1>(clas[i]), std::get<2>(clas[i])};
  }
}

std::vector<int> BuildSufmas(std::string& str) {
  std::vector<int> sufmas(2 * str.size());
  std::vector<int> classes(2 * str.size());
  Sort(str, sufmas, classes);
  for (size_t i = 1; i < str.size(); i *= 2) {
    std::vector<std::tuple<int, int, int>> clas_pair(str.size());
    for (size_t j = 0; j < str.size(); ++j) {
      clas_pair[j] = {classes[j], classes[(j + i) % str.size()], j};
    }
    SortPairs(clas_pair);
    int number = 0;
    for (size_t q = 0; q < str.size(); ++q) {
      if (q > 0 &&
          (std::get<0>(clas_pair[q]) != std::get<0>(clas_pair[q - 1]) ||
           std::get<1>(clas_pair[q]) != std::get<1>(clas_pair[q - 1]))) {
        ++number;
      }
      classes[std::get<2>(clas_pair[q])] = number;
      sufmas[q] = std::get<2>(clas_pair[q]);
    }
  }
  std::vector<int> mas(str.size());
  for (size_t j = 0; j < str.size(); ++j) {
    mas[j] = sufmas[j];
  }
  return mas;
}

int main() {
  PrepareIO();
  std::string str;
  std::cin >> str;
  std::vector<int> sufmas(str.size() + 1);
  sufmas = BuildSufmas(str);
  for (size_t i = 0; i < sufmas.size(); ++i) {
    std::cout << str[(sufmas[i] + str.size() - 1) % str.size()];
  }
}
