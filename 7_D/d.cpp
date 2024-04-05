// В задаче необходимо найти компоненты сильной связности
// ориентированного графа

#include <algorithm>
#include <iostream>
#include <vector>

std::vector<int> color;
std::vector<std::pair<int, int>> tout;
std::vector<int> strong_connectivity;
int index = 0;
int timer = 0;

class Graph {
 private:
  std::vector<std::vector<int>> sides_;
  std::vector<std::vector<int>> reversed_;

 public:
  explicit Graph(std::vector<std::vector<int>> vector, size_t count_nodes) {
    sides_.resize(count_nodes);
    reversed_.resize(count_nodes);
    for (size_t i = 0; i < vector.size(); ++i) {
      sides_[vector[i][0] - 1].push_back(vector[i][1] - 1);
      reversed_[vector[i][1] - 1].push_back(vector[i][0] - 1);
    }
  }

  std::vector<int> GetSides(int node) { return sides_[node]; }

  std::vector<int> GetReversedSides(int node) { return reversed_[node]; }
};

void DFS(int from, Graph& graph) {
  color[from] = 1;
  for (size_t i = 0; i < graph.GetSides(from).size(); ++i) {
    int to_node = graph.GetSides(from)[i];
    if (color[to_node] == 0) {
      DFS(to_node, graph);
    }
  }
  color[from] = 2;
  tout[from] = {timer++, from};
}

void DFSr(int from, Graph& graph) {
  color[from] = 1;
  for (size_t i = 0; i < graph.GetReversedSides(from).size(); ++i) {
    int to_node = graph.GetReversedSides(from)[i];
    if (color[to_node] == 0) {
      DFSr(to_node, graph);
    }
  }
  color[from] = 2;
  strong_connectivity[from] = index;
}

void BoostIO() {
  std::ios::sync_with_stdio(false);
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

void FindStrongConnection(size_t count_nodes, Graph& graph) {
  color.resize(count_nodes);
  tout.resize(count_nodes);
  strong_connectivity.resize(count_nodes);
  for (size_t i = 0; i < count_nodes; ++i) {
    if (color[i] == 0) {
      DFS(i, graph);
    }
  }

  std::sort(tout.begin(), tout.end());
  std::reverse(tout.begin(), tout.end());
  std::fill(color.begin(), color.end(), 0);

  for (size_t i = 0; i < count_nodes; ++i) {
    int node = tout[i].second;
    if (color[node] == 0) {
      DFSr(node, graph);
      ++index;
    }
  }
};

int main() {
  BoostIO();

  size_t count_sides;
  size_t count_nodes;
  std::cin >> count_nodes >> count_sides;
  std::vector<std::vector<int>> sides(count_sides, std::vector<int>(2));
  for (size_t i = 0; i < count_sides; ++i) {
    std::cin >> sides[i][0] >> sides[i][1];
  }
  Graph graph(sides, count_nodes);
  FindStrongConnection(count_nodes, graph);
  std::cout << index << "\n";
  for (size_t i = 0; i < count_nodes; ++i) {
    std::cout << strong_connectivity[i] + 1 << " ";
  }
}
