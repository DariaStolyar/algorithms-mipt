// В задаче необходимо найти площадь объединения прямоугольников
#include <algorithm>
#include <iostream>
#include <vector>

class Tree {
 public:
  Tree(const std::vector<int>& tree_length);

  void NewTree(size_t node, size_t start, size_t finish);

  void Update(size_t node, std::pair<size_t, size_t> start_finish, size_t left,
              size_t right, int change);

  int GetRootValue() { return tree_[1][0]; }

 private:
  std::vector<std::vector<int>> tree_;
  std::vector<int> tree_length_;
};

Tree::Tree(const std::vector<int>& tree_length) : tree_length_(tree_length) {
  tree_.resize(4 * tree_length.size());
}

void Tree::NewTree(size_t node, size_t start, size_t finish) {
  if (start == finish) {
    tree_[node] = {tree_length_[start], 0, 0};
    return;
  }
  size_t middle = (start + finish) / 2;
  NewTree(node * 2, start, middle);
  NewTree(node * 2 + 1, middle + 1, finish);
  tree_[node] = {tree_[node * 2][0] + tree_[node * 2 + 1][0], 0, 0};
}

void Tree::Update(size_t node, std::pair<size_t, size_t> start_finish,
                  size_t left, size_t right, int change) {
  size_t start = start_finish.first;
  size_t finish = start_finish.second;

  if (start == left && finish == right) {
    if (start == finish) {
      tree_[node] = {tree_[node][0], tree_[node][1] + change, 0};
      return;
    }
    tree_[node][1] += change;
    tree_[node][2] += change;
    return;
  }

  size_t middle = (start + finish) / 2;
  std::pair<size_t, size_t> new_start_finish;
  size_t first_son = 2 * node;
  size_t second_son = 2 * node + 1;
  tree_[first_son][1] += tree_[node][2];
  tree_[first_son][2] += tree_[node][2];
  tree_[second_son][1] += tree_[node][2];
  tree_[second_son][2] += tree_[node][2];
  tree_[node][2] = 0;

  if (left <= middle) {
    new_start_finish.first = start;
    new_start_finish.second = middle;
    Update(first_son, new_start_finish, left, std::min(right, middle), change);
  }

  if (right > middle) {
    new_start_finish.first = middle + 1;
    new_start_finish.second = finish;
    Update(second_son, new_start_finish, std::max(left, middle + 1), right,
           change);
  }

  if (tree_[first_son][1] < tree_[second_son][1]) {
    tree_[node][0] = tree_[first_son][0];
    tree_[node][1] = tree_[first_son][1];
  } else if (tree_[first_son][1] > tree_[2 * node + 1][1]) {
    tree_[node][0] = tree_[second_son][0];
    tree_[node][1] = tree_[second_son][1];
  } else {
    tree_[node][0] = tree_[first_son][0] + tree_[second_son][0];
    tree_[node][1] = tree_[second_son][1];
  }
}

void BoostIO() {
  std::ios::sync_with_stdio(false);
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

int main() {
  BoostIO();
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
      scanline.push_back({angles[0], angles[1], angles[3], 1});
      scanline.push_back({angles[2], angles[1], angles[3], -1});
      second_coordinates.push_back(angles[1]);
      second_coordinates.push_back(angles[3]);
    }
  }

  std::vector<int> compress_coordinates;
  std::vector<int> tree_lengths;
  std::sort(scanline.begin(), scanline.end());
  std::sort(second_coordinates.begin(), second_coordinates.end());

  int max_width = 0;
  int value = second_coordinates[0];
  compress_coordinates.push_back(value);
  tree_lengths.push_back(value);
  for (size_t i = 1; i < second_coordinates.size(); ++i) {
    max_width = std::max(max_width, second_coordinates[i]);
    if (second_coordinates[i] != value) {
      compress_coordinates.push_back(second_coordinates[i]);
      tree_lengths.push_back(second_coordinates[i] - value);
      value = second_coordinates[i];
    }
  }

  int length = compress_coordinates.size() - 1;
  Tree tree_coordinates(tree_lengths);
  tree_coordinates.NewTree(1, 0, length);
  int index = scanline[0][0];
  long long ans = 0;
  for (size_t i = 0; i < scanline.size(); ++i) {
    if (index != scanline[i][0]) {
      ans += (max_width - tree_coordinates.GetRootValue()) *
             static_cast<long long>(scanline[i][0] - index);
      index = scanline[i][0];
    }
    size_t left = std::lower_bound(compress_coordinates.begin(),
                                   compress_coordinates.end(), scanline[i][1]) -
                  compress_coordinates.begin();
    size_t right =
        std::lower_bound(compress_coordinates.begin(),
                         compress_coordinates.end(), scanline[i][2]) -
        compress_coordinates.begin();
    tree_coordinates.Update(1, {0, length}, left + 1, right, scanline[i][3]);
  }
  std::cout << ans;
}
