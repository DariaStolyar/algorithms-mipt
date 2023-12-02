 #include <algorithm>
#include <iostream>
#include <vector>

std::vector<std::vector<int>> tree;
std::vector<std::vector<int>> first;
std::vector<int> tree_to_int;
std::vector<int> tree_length;

void NewTree(size_t node, int start, int finish) {
  if (start == finish) {
    tree[node] = {tree_length[start], 0, 0};
    return;
  }
  int middle = (start + finish) / 2;
  NewTree(node * 2, start, middle);
  NewTree(node * 2 + 1, middle + 1, finish);
  tree[node] = {tree[node * 2][0] + tree[node * 2 + 1][0], 0, 0};
}

void Update(size_t node, std::pair<int, int> start_finish, int left, int right,
            int change) {
  int start = start_finish.first;
  int finish = start_finish.second;
  if (start == left && finish == right) {
    if (start == finish) {
      tree[node] = {tree[node][0], tree[node][1] + change, 0};
      return;
    }
    tree[node][1] += change;
    tree[node][2] += change;
    return;
  }
  int middle = (start + finish) / 2;
  std::pair<int, int> new_start_finish;
  tree[2 * node][1] += tree[node][2];
  tree[2 * node][2] += tree[node][2];
  tree[2 * node + 1][1] += tree[node][2];
  tree[2 * node + 1][2] += tree[node][2];
  tree[node][2] = 0;
  if (left <= middle) {
    new_start_finish.first = start;
    new_start_finish.second = middle;
    Update(2 * node, new_start_finish, left, std::min(right, middle), change);
  }
  if (right > middle) {
    new_start_finish.first = middle + 1;
    new_start_finish.second = finish;
    Update(2 * node + 1, new_start_finish, std::max(left, middle + 1), right,
           change);
  }
  if (tree[2 * node][1] < tree[2 * node + 1][1]) {
    tree[node][0] = tree[2 * node][0];
    tree[node][1] = tree[2 * node][1];
  } else if (tree[2 * node][1] > tree[2 * node + 1][1]) {
    tree[node][0] = tree[2 * node + 1][0];
    tree[node][1] = tree[2 * node + 1][1];
  } else {
    tree[node][0] = tree[node * 2][0] + tree[node * 2 + 1][0];
    tree[node][1] = tree[2 * node + 1][1];
  }
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
  std::cin >> count;
  if (count == 0) {
    std::cout << 0;
    return 0;
  }
  std::vector<std::vector<int>> scanline;
  std::vector<int> second_coordinates;
  for (size_t i = 0; i < count; ++i) {
    std::vector<int> angles(4);
    std::cin >> angles[0] >> angles[1] >> angles[2] >> angles[3];
    if (angles[0] < angles[2] and angles[1] < angles[3]) {
      first.push_back(angles);
      scanline.push_back({angles[0], angles[1], angles[3], 1});
      scanline.push_back({angles[2], angles[1], angles[3], -1});
      second_coordinates.push_back(angles[1]);
      second_coordinates.push_back(angles[3]);
    }
  }
  int max_width = 0;
  std::sort(scanline.begin(), scanline.end());
  std::sort(second_coordinates.begin(), second_coordinates.end());
  int value = second_coordinates[0];
  tree_to_int.push_back(value);
  tree_length.push_back(value);
  for (size_t i = 1; i < second_coordinates.size(); ++i) {
    max_width = std::max(max_width, second_coordinates[i]);
    if (second_coordinates[i] != value) {
      tree_to_int.push_back(second_coordinates[i]);
      tree_length.push_back(second_coordinates[i] - value);
      value = second_coordinates[i];
    }
  }
  int length = tree_to_int.size() - 1;
  tree.resize(4 * length);
  NewTree(1, 0, length);
  int index = scanline[0][0];
  long long ans = 0;
  for (size_t i = 0; i < scanline.size(); ++i) {
    if (index != scanline[i][0]) {
      ans += (max_width - tree[1][0]) *
             static_cast<long long>(scanline[i][0] - index);
      index = scanline[i][0];
    }
    int left = std::lower_bound(tree_to_int.begin(), tree_to_int.end(),
                                scanline[i][1]) -
               tree_to_int.begin();
    int right = std::lower_bound(tree_to_int.begin(), tree_to_int.end(),
                                 scanline[i][2]) -
                tree_to_int.begin();
    Update(1, {0, length}, left + 1, right, scanline[i][3]);
  }
  std::cout << ans;
}
