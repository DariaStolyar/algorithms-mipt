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
 public:
  explicit Graph(size_t count_nodes) : sides_(count_nodes) {}

  void AddSide(int node1, int node2, int weight) {
    sides_[node1].push_back({node2, weight});
    sides_[node2].push_back({node1, weight});
  }

  std::vector<std::pair<int, int>> GetSides(int node) const {
    return sides_[node];
  }

 private:
  std::vector<std::vector<std::pair<int, int>>> sides_;
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
    Graph graph(count_nodes);
    for (size_t j = 0; j < count_sides; ++j) {
      int node1;
      int node2;
      int weight;
      std::cin >> node1 >> node2 >> weight;
      graph.AddSide(node1, node2, weight);
    }
    size_t node;
    std::cin >> node;
    std::vector<int> dist = FindDistances(count_nodes, graph, node);
    for (size_t j = 0; j < dist.size(); ++j) {
      std::cout << dist[j] << " ";
    }
    std::cout << "\n";
  }
}
