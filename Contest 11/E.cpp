#include <algorithm>
#include <climits>
#include <iostream>
#include <map>
#include <queue>
#include <vector>

const long long cCodeZ = 122;
const long long cCountLetters = 27;
const std::string cAlphabet = "abcdefghijklmnopqrstuvwxyz";

void PrepareIO() {
  std::ios::sync_with_stdio(false);
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

void Sort(std::string& str, std::vector<long long>& sort,
          std::vector<long long>& classes) {
  std::vector<long long> cnt(cCodeZ + 1, 0);
  for (size_t i = 0; i < str.size(); ++i) {
    ++cnt[str[i]];
  }
  for (size_t i = 1; i < cnt.size(); ++i) {
    cnt[i] += cnt[i - 1];
  }
  for (long long i = static_cast<long long>(str.size()) - 1; i >= 0; --i) {
    sort[--cnt[str[i]]] = i;
  }
  long long number = 0;
  for (size_t i = 0; i < str.size(); ++i) {
    if (i > 0 && str[sort[i]] != str[sort[i - 1]]) {
      ++number;
    }
    classes[sort[i]] = number;
  }
}

void SortPairs(
        std::vector<std::tuple<long long, long long, long long>>& clas_pair) {
  std::vector<std::tuple<long long, long long, long long>> clas(
          clas_pair.size());
  for (size_t i = 0; i < clas_pair.size(); ++i) {
    clas[i] = {std::get<0>(clas_pair[i]), std::get<1>(clas_pair[i]),
               std::get<2>(clas_pair[i])};
  }
  std::vector<long long> cnt(clas_pair.size(), 0);
  for (size_t i = 0; i < clas_pair.size(); ++i) {
    ++cnt[std::get<1>(clas[i])];
  }
  for (size_t i = 1; i < cnt.size(); ++i) {
    cnt[i] += cnt[i - 1];
  }
  for (long long i = static_cast<long long>(clas_pair.size()) - 1; i >= 0;
       --i) {
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
  for (long long i = static_cast<long long>(clas_pair.size()) - 1; i >= 0;
       --i) {
    clas_pair[--cnt[std::get<0>(clas[i])]] = {
            std::get<0>(clas[i]), std::get<1>(clas[i]), std::get<2>(clas[i])};
  }
}

std::vector<long long> BuildSufmas(std::string str) {
  std::vector<long long> sufmas(2 * str.size());
  std::vector<long long> classes(2 * str.size());
  Sort(str, sufmas, classes);
  for (size_t i = 1; i < str.size(); i *= 2) {
    std::vector<std::tuple<long long, long long, long long>> clas_pair(
            str.size());
    for (size_t j = 0; j < str.size(); ++j) {
      clas_pair[j] = {classes[j], classes[(j + i) % str.size()], j};
    }
    SortPairs(clas_pair);
    long long number = 0;
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
  std::vector<long long> mas(str.size());
  for (size_t j = 0; j < str.size(); ++j) {
    mas[j] = sufmas[j];
  }
  return mas;
}

std::string BWT(std::string& str) {
  std::string find(str.size(), ' ');
  std::vector<long long> sufmas(str.size() + 1);
  sufmas = BuildSufmas(str);
  for (size_t i = 0; i < sufmas.size(); ++i) {
    find[i] = str[(sufmas[i] + str.size() - 1) % str.size()];
  }
  return find;
}

std::string BWTr(std::string& str, long long index) {
  std::string find(str.size(), ' ');
  std::vector<long long> count(cCountLetters, 0);
  std::vector<long long> dp(str.size());
  for (size_t i = 0; i < str.size(); ++i) {
    count[str[i] - '`'] += 1;
  }
  std::vector<long long> pref(cCountLetters);
  for (size_t i = 0; i < pref.size(); ++i) {
    if (i == 0) {
      pref[i] = count[i];
      count[i] = 0;
    } else {
      pref[i] = pref[i - 1] + count[i];
      count[i] = pref[i] - count[i];
    }
  }
  for (size_t i = 0; i < str.size(); ++i) {
    dp[count[str[i] - '`']] = i;
    count[str[i] - '`'] += 1;
  }
  long long number = dp[index];
  for (size_t i = 0; i < str.size(); ++i) {
    find[i] = str[number];
    number = dp[number];
  }
  return find;
}

std::string MTF(std::string& str) {
  std::string changed_alphabet = cAlphabet;
  std::string find(str.size(), ' ');
  for (size_t i = 0; i < str.size(); ++i) {
    long long index = 0;
    for (size_t j = 0; j < changed_alphabet.size(); ++j) {
      if (changed_alphabet[j] == str[i]) {
        index = j;
        break;
      }
    }
    std::string new_alphabet(changed_alphabet.size(), ' ');
    for (long long j = 0; j < static_cast<long long>(changed_alphabet.size());
         ++j) {
      if (j == 0) {
        new_alphabet[j] = changed_alphabet[index];
      } else if (j <= index) {
        new_alphabet[j] = changed_alphabet[j - 1];
      } else {
        new_alphabet[j] = changed_alphabet[j];
      }
    }
    changed_alphabet = new_alphabet;
    find[i] = cAlphabet[index];
  }
  return find;
}

std::string MTFr(std::string& str) {
  std::string changed_alphabet = cAlphabet;
  std::string find(str.size(), ' ');
  for (size_t i = 0; i < str.size(); ++i) {
    long long index = 0;
    for (size_t j = 0; j < changed_alphabet.size(); ++j) {
      if (cAlphabet[j] == str[i]) {
        index = j;
        break;
      }
    }
    find[i] = changed_alphabet[index];
    std::string new_alphabet(changed_alphabet.size(), ' ');
    for (long long j = 0; j < static_cast<long long>(changed_alphabet.size());
         ++j) {
      if (j == 0) {
        new_alphabet[j] = changed_alphabet[index];
      } else if (j <= index) {
        new_alphabet[j] = changed_alphabet[j - 1];
      } else {
        new_alphabet[j] = changed_alphabet[j];
      }
    }
    changed_alphabet = new_alphabet;
  }
  return find;
}

std::string RLE(std::string& str) {
  std::string find;
  char letter = ' ';
  long long count = 0;
  for (size_t i = 0; i < str.size(); ++i) {
    if (letter == ' ') {
      letter = str[i];
      count = 1;
    } else if (str[i] == letter) {
      count += 1;
    } else {
      find += letter;
      find += std::to_string(count);
      letter = str[i];
      count = 1;
    }
  }
  find += letter;
  find += std::to_string(count);
  return find;
}

std::string RLEr(std::string& str) {
  std::string find;
  char letter = ' ';
  std::string count;
  for (size_t i = 0; i < str.size(); ++i) {
    if (letter == ' ' and count.empty()) {
      letter = str[i];
    } else if ((str[i] - 'a' <= cCountLetters - 1) and (str[i] - 'a' >= 0) and
               !count.empty()) {
      for (long long j = 0; j < std::stoi(count); ++j) {
        find += letter;
      }
      count.clear();
      letter = str[i];
    } else {
      count += str[i];
    }
  }
  if (!count.empty()) {
    for (long long j = 0; j < std::stoi(count); ++j) {
      find += letter;
    }
  }
  return find;
}

int main() {
  PrepareIO();
  size_t mode;
  std::cin >> mode;
  std::string str;
  std::cin >> str;
  std::string encode;
  if (mode == 1) {
    encode = BWT(str);
    encode = MTF(encode);
    encode = RLE(encode);
  } else {
    long long index;
    std::cin >> index;
    encode = RLEr(str);
    encode = MTFr(encode);
    encode = BWTr(encode, index);
  }
  for (size_t i = 0; i < encode.size(); ++i) {
    std::cout << encode[i];
  }
}
