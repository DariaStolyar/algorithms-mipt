// В задаче необходимо найти расстояния от одной вершины
// до всех остальных в ориентированном графе

#include <algorithm>
#include <climits>
#include <iostream>
#include <queue>
#include <vector>

using QueueType =
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                        std::greater<>>;
const int cDist = 2009000999;

class Graph {
 private:
  std::vector<std::vector<std::pair<int, int>>> sides_;

 public:
  explicit Graph(const std::vector<std::vector<int>>& vector,
                 size_t count_nodes)
      : sides_(count_nodes) {
    for (size_t i = 0; i < vector.size(); ++i) {
      sides_[vector[i][0]].push_back({vector[i][1], vector[i][2]});
      sides_[vector[i][1]].push_back({vector[i][0], vector[i][2]});
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
            std::vector<int>& dist) {
  for (auto pair : graph.GetSides(node)) {
    if (dist[pair.first] > dist[node] + pair.second) {
      dist[pair.first] = dist[node] + pair.second;
      min_heap.push({dist[pair.first], pair.first});
    }
  }
}

std::vector<int> FindDistances(size_t count_nodes, const Graph& graph,
                               size_t node) {
  std::vector<int> distances(count_nodes, cDist);
  distances[node] = 0;
  QueueType min_heap;
  min_heap.push({0, node});
  while (!min_heap.empty()) {
    auto dist_node = min_heap.top();
    min_heap.pop();
    if (dist_node.first > distances[dist_node.second]) {
      continue;
    }
    Expand(dist_node.second, graph, min_heap, distances);
  }
  return distances;
}

int main() {
  BoostIO();

  size_t count_tests;
  std::cin >> count_tests;
  for (size_t i = 0; i < count_tests; ++i) {
    size_t count_sides;
    size_t count_nodes;
    std::cin >> count_nodes >> count_sides;
    std::vector<std::vector<int>> sides(count_sides, std::vector<int>(3));
    for (size_t j = 0; j < count_sides; ++j) {
      std::cin >> sides[j][0] >> sides[j][1] >> sides[j][2];
    }
    Graph graph(sides, count_nodes);
    size_t node;
    std::cin >> node;
    std::vector<int> dist = FindDistances(count_nodes, graph, node);
    for (size_t j = 0; j < dist.size(); ++j) {
      std::cout << dist[j] << " ";
    }
    std::cout << "\n";
  }
}
