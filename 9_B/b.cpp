// В задаче необходимо найти MST
#include <algorithm>
#include <climits>
#include <iostream>
#include <queue>
#include <vector>

using QueueType =
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                        std::greater<>>;

class Graph {
 private:
  std::vector<std::vector<std::pair<int, int>>> sides_;

 public:
  explicit Graph(const std::vector<std::vector<int>>& vector,
                 size_t count_nodes)
      : sides_(count_nodes) {
    for (size_t i = 0; i < vector.size(); ++i) {
      sides_[vector[i][0] - 1].push_back({vector[i][1] - 1, vector[i][2]});
      sides_[vector[i][1] - 1].push_back({vector[i][0] - 1, vector[i][2]});
    }
  }

  std::vector<std::pair<int, int>> GetSides(int node) const {
    return sides_[node];
  }
};

void BoostIO() {
  std::ios::sync_with_stdio(false);
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

void Expand(int node, const Graph& graph, QueueType& min_heap,
            std::vector<int>& dist, std::vector<int> in_mst) {
  for (auto pair : graph.GetSides(node)) {
    if (in_mst[pair.first] == 1) {
      continue;
    }
    if (dist[pair.first] > pair.second) {
      dist[pair.first] = pair.second;
      min_heap.push({dist[pair.first], pair.first});
    }
  }
}

int FindMST(size_t count_nodes, const Graph& graph) {
  std::vector<int> distances(count_nodes, INT_MAX);
  std::vector<int> in_mst(count_nodes);

  in_mst[0] = 1;
  distances[0] = 0;
  QueueType min_heap;
  min_heap.push({0, 0});

  while (!min_heap.empty()) {
    auto dist_node = min_heap.top();
    min_heap.pop();
    if (dist_node.first > distances[dist_node.second]) {
      continue;
    }
    in_mst[dist_node.second] = 1;
    Expand(dist_node.second, graph, min_heap, distances, in_mst);
  }
  int sum_mst = 0;
  for (size_t i = 0; i < count_nodes; ++i) {
    sum_mst += distances[i];
  }
  return sum_mst;
}

int main() {
  BoostIO();

  size_t count_sides;
  size_t count_nodes;
  std::cin >> count_nodes >> count_sides;
  std::vector<std::vector<int>> sides(count_sides, std::vector<int>(3));
  for (size_t j = 0; j < count_sides; ++j) {
    std::cin >> sides[j][0] >> sides[j][1] >> sides[j][2];
  }
  Graph graph(sides, count_nodes);
  int dist = FindMST(count_nodes, graph);
  std::cout << dist;
}
