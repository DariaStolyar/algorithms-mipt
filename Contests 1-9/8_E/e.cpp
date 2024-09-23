// В задаче необходимо найти отрицательный цикл

#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

void BoostIO() {
  std::ios::sync_with_stdio(false);
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

class Graph {
 private:
  std::vector<std::vector<std::pair<int, int>>> sides_;
  const int cMax = 100000;

 public:
  explicit Graph(const std::vector<std::vector<int>>& vector,
                 size_t count_nodes)
      : sides_(count_nodes) {
    for (size_t i = 0; i < count_nodes; ++i) {
      for (size_t j = 0; j < count_nodes; ++j) {
        if (vector[i][j] != cMax) {
          sides_[i].push_back({j, vector[i][j]});
        }
      }
    }
  }

  std::vector<std::pair<int, int>> GetSides(int node) const {
    return sides_[node];
  }
};

std::pair<bool, std::vector<long long>> FindNegativeCycle(int count_nodes,
                                                          const Graph& graph) {
  std::vector<long long> dp(count_nodes, 0);
  std::vector<long long> prev(count_nodes, -1);
  for (long long k = 0; k < count_nodes - 2; ++k) {
    for (long long i = 0; i < count_nodes; ++i) {
      for (auto [j, cost] : graph.GetSides(i)) {
        if (dp[j] > dp[i] + cost) {
          dp[j] = dp[i] + cost;
          prev[j] = i;
        }
      }
    }
  }
  bool have_negative = false;
  int node = 0;
  for (long long i = 0; i < count_nodes; ++i) {
    for (auto [j, cost] : graph.GetSides(i)) {
      if (dp[j] > dp[i] + cost) {
        prev[j] = i;
        have_negative = true;
        node = j;
      }
    }
  }
  if (!have_negative) {
    return {false, {}};
  }
  for (int i = 0; i < count_nodes; ++i) {
    node = prev[node];
  }
  std::vector<long long> negative_cycle;
  negative_cycle.push_back(node);
  while (prev[negative_cycle[negative_cycle.size() - 1]] != node) {
    negative_cycle.push_back(prev[negative_cycle[negative_cycle.size() - 1]]);
  }
  negative_cycle.push_back(node);
  std::reverse(negative_cycle.begin(), negative_cycle.end());
  return {true, negative_cycle};
}

int main() {
  BoostIO();

  int count_nodes;
  std::cin >> count_nodes;
  std::vector<std::vector<int>> sides(count_nodes,
                                      std::vector<int>(count_nodes));
  for (int i = 0; i < count_nodes; ++i) {
    for (int j = 0; j < count_nodes; ++j) {
      std::cin >> sides[i][j];
    }
  }
  Graph graph(sides, count_nodes);
  std::pair<bool, std::vector<long long>> finding =
      FindNegativeCycle(count_nodes, graph);
  if (finding.first) {
    std::cout << "YES"
              << "\n";
    std::cout << finding.second.size() << "\n";
    for (auto i : finding.second) {
      std::cout << i + 1 << " ";
    }
  } else {
    std::cout << "NO";
  }
}
