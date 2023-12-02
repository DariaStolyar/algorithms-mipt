 #include <algorithm>
#include <iostream>
#include <vector>

std::vector<std::vector<int>> tree;
std::vector<int> first;

std::vector<int> Merge(std::vector<int>& left_a, std::vector<int>& right_a) {
  std::vector<int> sum_a(left_a.size() + right_a.size());
  size_t i_a = 0;
  size_t j_a = 0;
  while (i_a < left_a.size() || j_a < right_a.size()) {
    if (j_a == right_a.size() ||
        (i_a < left_a.size() && left_a[i_a] <= right_a[j_a])) {
      sum_a[i_a + j_a] = left_a[i_a];
      ++i_a;
    } else {
      sum_a[i_a + j_a] = right_a[j_a];
      ++j_a;
    }
  }
  return sum_a;
}

void NewTree(size_t node, int start, int finish) {
  if (start == finish) {
    tree[node] = {first[start]};
    return;
  }
  int middle = (start + finish) / 2;
  NewTree(node * 2, start, middle);
  NewTree(node * 2 + 1, middle + 1, finish);
  tree[node] = Merge(tree[node * 2], tree[node * 2 + 1]);
}

long long GetMax(size_t node, std::pair<int, int> start_finish, int left,
                 int right, std::pair<int, int> borders) {
  int start = start_finish.first;
  int finish = start_finish.second;
  if (borders.first > tree[node][tree[node].size() - 1] or
      borders.second < tree[node][0]) {
    return 0;
  }
  if (start == left && finish == right) {
    long long index_start =
        std::lower_bound(tree[node].begin(), tree[node].end(), borders.first) -
        tree[node].begin();
    long long index_finish =
        std::upper_bound(tree[node].begin(), tree[node].end(), borders.second) -
        tree[node].begin();
    return index_finish - index_start;
  }
  std::pair<int, int> new_start_finish;
  int middle = (start + finish) / 2;
  long long result = 0;
  if (left <= middle) {
    new_start_finish.first = start;
    new_start_finish.second = middle;
    result += GetMax(2 * node, new_start_finish, left, std::min(right, middle),
                     borders);
  }
  if (right > middle) {
    new_start_finish.first = middle + 1;
    new_start_finish.second = finish;
    result += GetMax(2 * node + 1, new_start_finish, std::max(left, middle + 1),
                     right, borders);
  }
  return result;
}

void Speed() {
  std::ios::sync_with_stdio(false);
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
}

int main() {
  Speed();
  size_t count;
  size_t count_query;
  std::cin >> count >> count_query;
  first.resize(count);
  tree.resize(4 * count);
  for (size_t i = 0; i < count; ++i) {
    std::cin >> first[i];
  }
  NewTree(1, 0, count - 1);
  for (size_t i = 0; i < count_query; ++i) {
    int left;
    int right;
    std::cin >> left >> right;
    --left;
    --right;
    std::pair<int, int> borders;
    std::cin >> borders.first >> borders.second;
    std::cout << GetMax(1, {0, count - 1}, left, right, borders) << "\n";
  }
}
