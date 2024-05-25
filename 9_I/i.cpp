// В задаче необходимо найти минимальное вершинное покрытие
// из максимального паросочетания
#include <algorithm>
#include <iostream>
#include <vector>

class Graph {
 private:
  std::vector<std::vector<int>> sides_;

 public:
  explicit Graph(size_t count_nodes) : sides_(count_nodes) {}

  std::vector<int> GetSides(int node) const { return sides_[node]; }

  void AddSide(int node1, int node2) { sides_[node1].push_back(node2); }
};

void BoostIO() {
  std::ios::sync_with_stdio(false);
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

void DFS(int from, Graph& graph, std::vector<int>& color) {
  color[from] = 1;
  for (size_t i = 0; i < graph.GetSides(from).size(); ++i) {
    int to_node = graph.GetSides(from)[i];
    if (color[to_node] == 0) {
      DFS(to_node, graph, color);
    }
  }
}

int FindMinVertexCover(size_t count_nodes1, size_t count_nodes2, Graph& graph,
                       std::vector<int>& match,
                       std::vector<std::vector<int>>& vertex_cover) {
  Graph or_graph(count_nodes1 + count_nodes2);
  std::vector<int> color(count_nodes1 + count_nodes2);

  for (size_t i = 0; i < count_nodes1; ++i) {
    for (auto j : graph.GetSides(i)) {
      if (match[i] == j) {
        or_graph.AddSide(match[i] + count_nodes1, i);
      } else {
        or_graph.AddSide(i, j + count_nodes1);
      }
    }
  }

  for (size_t i = 0; i < count_nodes1; ++i) {
    if (match[i] == -1) {
      DFS(i, or_graph, color);
    }
  }

  int count = 0;
  for (size_t i = 0; i < count_nodes1 + count_nodes2; ++i) {
    if (i < count_nodes1 and color[i] == 0) {
      vertex_cover[0].push_back(i);
      ++count;
    }
    if (i >= count_nodes1 and color[i] == 1) {
      vertex_cover[1].push_back(i - count_nodes1);
      ++count;
    }
  }
  return count;
}

int main() {
  BoostIO();

  size_t count_nodes1;
  size_t count_nodes2;
  std::cin >> count_nodes1 >> count_nodes2;
  Graph graph(count_nodes1);

  for (size_t i = 0; i < count_nodes1; ++i) {
    size_t count;
    std::cin >> count;
    int node;
    for (size_t j = 0; j < count; ++j) {
      std::cin >> node;
      graph.AddSide(i, node - 1);
    }
  }

  std::vector<int> match(count_nodes1);
  for (size_t i = 0; i < count_nodes1; ++i) {
    std::cin >> match[i];
    match[i] -= 1;
  }

  std::vector<std::vector<int>> vertex_cover(2);
  int count = FindMinVertexCover(count_nodes1, count_nodes2, graph, match,
                                 vertex_cover);

  std::cout << count << "\n";
  std::cout << vertex_cover[0].size() << " ";
  for (auto i : vertex_cover[0]) {
    std::cout << i + 1 << " ";
  }
  std::cout << "\n";
  std::cout << vertex_cover[1].size() << " ";
  for (auto i : vertex_cover[1]) {
    std::cout << i + 1 << " ";
  }
}
