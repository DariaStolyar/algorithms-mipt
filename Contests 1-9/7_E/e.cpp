// В задаче необходимо найти мосты в неориентированном графе

#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

struct ObjectsForFindBridges {
  std::vector<int> color;
  std::vector<int> tin;
  std::vector<int> return_node;
  std::vector<std::pair<int, int>> bridges;
  int timer = 0;
  explicit ObjectsForFindBridges(size_t count_nodes)
      : color(count_nodes), tin(count_nodes), return_node(count_nodes) {}
};

class Graph {
 private:
  std::vector<std::vector<int>> sides_;

 public:
  explicit Graph(const std::vector<std::vector<int>>& vector,
                 size_t count_nodes) {
    sides_.resize(count_nodes);
    for (size_t i = 0; i < vector.size(); ++i) {
      sides_[vector[i][0] - 1].push_back(vector[i][1] - 1);
      sides_[vector[i][1] - 1].push_back(vector[i][0] - 1);
    }
  }

  std::vector<int> GetSides(int node) const { return sides_[node]; }
};

void DFS(int from, const Graph& graph, int parent_from,
         ObjectsForFindBridges& finding) {
  finding.tin[from] = finding.timer++;
  finding.return_node[from] = finding.tin[from];
  finding.color[from] = 1;
  std::vector<int> sides_from = graph.GetSides(from);
  for (size_t i = 0; i < sides_from.size(); ++i) {
    int to_node = sides_from[i];
    if (to_node == parent_from) {
      continue;
    }
    if (finding.color[to_node] == 0) {
      DFS(to_node, graph, from, finding);
      finding.return_node[from] =
          std::min(finding.return_node[from], finding.return_node[to_node]);
      if (finding.return_node[to_node] == finding.tin[to_node]) {
        finding.bridges.push_back({from + 1, to_node + 1});
      }
    } else {
      finding.return_node[from] =
          std::min(finding.return_node[from], finding.tin[to_node]);
    }
  }
}

void BoostIO() {
  std::ios::sync_with_stdio(false);
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

std::vector<int> FindBridges(size_t count_sides, size_t count_nodes,
                             const std::vector<std::vector<int>>& sides,
                             const Graph& graph) {
  std::map<std::pair<int, int>, std::pair<bool, int>> sides_map;
  for (size_t i = 0; i < count_sides; ++i) {
    std::pair<int, int> side = {sides[i][0], sides[i][1]};
    std::pair<int, int> side_r = {sides[i][1], sides[i][0]};
    if (sides_map.find(side) == sides_map.end()) {
      sides_map.insert({side, {false, i}});
      sides_map.insert({side_r, {false, i}});
    } else {
      sides_map[side] = {true, i};
      sides_map[side_r] = {true, i};
    }
  }
  ObjectsForFindBridges finding(count_nodes);
  for (size_t i = 0; i < count_nodes; ++i) {
    if (finding.color[i] == 0) {
      DFS(i, graph, -1, finding);
    }
  }
  std::vector<int> ans;
  for (size_t i = 0; i < finding.bridges.size(); ++i) {
    if (sides_map.find(finding.bridges[i]) == sides_map.end()) {
      continue;
    }
    if (sides_map[finding.bridges[i]].first) {
      continue;
    }
    ans.push_back(sides_map[finding.bridges[i]].second);
  }
  std::sort(ans.begin(), ans.end());
  return ans;
}

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
  std::vector<int> ans = FindBridges(count_sides, count_nodes, sides, graph);
  std::cout << ans.size() << "\n";
  for (int ans_i : ans) {
    std::cout << ans_i + 1 << " ";
  }
}
