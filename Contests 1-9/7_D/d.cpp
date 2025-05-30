// В задаче необходимо найти компоненты сильной связности
// ориентированного графа

#include <algorithm>
#include <iostream>
#include <vector>

struct ObjectsForFindConnectivity {
  std::vector<int> color;
  std::vector<std::pair<int, int>> tout;
  std::vector<int> strong_connectivity;
  int index = 0;
  int timer = 0;
  explicit ObjectsForFindConnectivity(size_t count_nodes)
      : color(count_nodes),
        tout(count_nodes),
        strong_connectivity(count_nodes) {}
};

class Graph {
 private:
  std::vector<std::vector<int>> sides_;

 public:
  explicit Graph(const std::vector<std::vector<int>>& vector,
                 size_t count_nodes)
      : sides_(count_nodes) {
    for (size_t i = 0; i < vector.size(); ++i) {
      sides_[vector[i][0] - 1].push_back(vector[i][1] - 1);
    }
  }

  std::vector<int> GetSides(int node) const { return sides_[node]; }
};

void DFS(int from, const Graph& graph, ObjectsForFindConnectivity& finding,
         bool find_tout) {
  finding.color[from] = 1;
  for (size_t i = 0; i < graph.GetSides(from).size(); ++i) {
    int to_node = graph.GetSides(from)[i];
    if (finding.color[to_node] == 0) {
      DFS(to_node, graph, finding, find_tout);
    }
  }
  finding.color[from] = 2;
  if (find_tout) {
    finding.tout[from] = {finding.timer++, from};
  }
  finding.strong_connectivity[from] = finding.index;
}

void BoostIO() {
  std::ios::sync_with_stdio(false);
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

std::vector<int> FindStrongConnection(size_t count_nodes, const Graph& graph,
                                      const Graph& graph_r) {
  ObjectsForFindConnectivity finding(count_nodes);
  for (size_t i = 0; i < count_nodes; ++i) {
    if (finding.color[i] == 0) {
      DFS(i, graph, finding, true);
    }
  }

  std::sort(finding.tout.begin(), finding.tout.end());
  std::reverse(finding.tout.begin(), finding.tout.end());
  std::fill(finding.color.begin(), finding.color.end(), 0);

  for (size_t i = 0; i < count_nodes; ++i) {
    int node = finding.tout[i].second;
    if (finding.color[node] == 0) {
      DFS(node, graph_r, finding, false);
      ++finding.index;
    }
  }
  return finding.strong_connectivity;
};

int main() {
  BoostIO();

  size_t count_sides;
  size_t count_nodes;
  std::cin >> count_nodes >> count_sides;
  std::vector<std::vector<int>> sides(count_sides, std::vector<int>(2));
  std::vector<std::vector<int>> sides_r(count_sides, std::vector<int>(2));
  for (size_t i = 0; i < count_sides; ++i) {
    std::cin >> sides[i][0] >> sides[i][1];
    sides_r[i][0] = sides[i][1];
    sides_r[i][1] = sides[i][0];
  }
  Graph graph(sides, count_nodes);
  Graph graph_r(sides_r, count_nodes);
  auto strong_connection = FindStrongConnection(count_nodes, graph, graph_r);
  auto maximum =
      *std::max_element(strong_connection.begin(), strong_connection.end());
  std::cout << maximum + 1 << "\n";
  for (size_t i = 0; i < count_nodes; ++i) {
    std::cout << strong_connection[i] + 1 << " ";
  }
}
