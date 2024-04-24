// В задаче необходимо найти решение восьминашек

#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

const int cSize = 9;

void BoostIO() {
  std::ios::sync_with_stdio(false);
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

struct Node {
  std::vector<int> sost;
  int pos0;
  std::string str;
};

class Graph {
 public:
  std::unordered_map<std::string, Node> sides;
  explicit Graph() = default;

  std::string AddNode(std::vector<int> sost) {
    std::string str;
    int pos_nul;
    for (int i = 0; i < cSize; ++i) {
      str += static_cast<char>(sost[i] + '0');
      if (sost[i] == 0) {
        pos_nul = i;
      }
    }
    sides[str] = Node({sost, pos_nul, str});
    return str;
  }
};

std::vector<Node> NextPositions(Node now_node) {
  const int cGood = 6;
  std::vector<Node> nexts;
  if (now_node.pos0 > 2) {
    std::vector<int> new_sost = now_node.sost;
    std::swap(new_sost[now_node.pos0], new_sost[now_node.pos0 - 3]);
    std::string str;
    for (int i = 0; i < cSize; ++i) {
      str += static_cast<char>(new_sost[i] + '0');
    }
    nexts.push_back({new_sost, now_node.pos0 - 3, str});
  }
  if (now_node.pos0 < cGood) {
    std::vector<int> new_sost = now_node.sost;
    std::swap(new_sost[now_node.pos0], new_sost[now_node.pos0 + 3]);
    std::string str;
    for (int i = 0; i < cSize; ++i) {
      str += static_cast<char>(new_sost[i] + '0');
    }
    nexts.push_back({new_sost, now_node.pos0 + 3, str});
  }
  if (now_node.pos0 % 3 != 0) {
    std::vector<int> new_sost = now_node.sost;
    std::swap(new_sost[now_node.pos0], new_sost[now_node.pos0 - 1]);
    std::string str;
    for (int i = 0; i < cSize; ++i) {
      str += static_cast<char>(new_sost[i] + '0');
    }
    nexts.push_back({new_sost, now_node.pos0 - 1, str});
  }
  if (now_node.pos0 % 3 != 2) {
    std::vector<int> new_sost = now_node.sost;
    std::swap(new_sost[now_node.pos0], new_sost[now_node.pos0 + 1]);
    std::string str;
    for (int i = 0; i < cSize; ++i) {
      str += static_cast<char>(new_sost[i] + '0');
    }
    nexts.push_back({new_sost, now_node.pos0 + 1, str});
  }
  return nexts;
}

bool HaveAnswer(std::vector<int> sost) {
  int invers = 0;
  for (int i = 0; i < cSize; ++i) {
    for (int j = i + 1; j < cSize; ++j) {
      if (sost[i] != 0 and sost[j] != 0 and sost[i] > sost[j]) {
        invers += 1;
      }
    }
  }
  return invers % 2 == 0;
}

using QueueType = std::priority_queue<std::pair<int, std::string>,
                                      std::vector<std::pair<int, std::string>>,
                                      std::greater<>>;

int ManchetRast(std::vector<int> sost1) {
  int rast = 0;
  for (int i = 0; i < cSize; ++i) {
    if (sost1[i] == 0) {
      continue;
    }
    int str_v = (sost1[i] - 1) / 3;
    int col_v = (sost1[i] - 1) % 3;
    rast += abs(str_v - (i / 3)) + abs(col_v - (i % 3));
  }
  return rast;
}

void Expand(Node& node, Graph& graph, QueueType& min_heap,
            std::unordered_map<std::string, std::pair<int, int>>& dist,
            std::unordered_map<std::string, std::string>& parent) {
  for (const auto& pair : NextPositions(node)) {
    graph.AddNode(pair.sost);
    if (!dist.contains(pair.str) or
        dist[pair.str].first > dist[node.str].first + 1) {
      dist[pair.str].first = dist[node.str].first + 1;
      dist[pair.str].second = dist[node.str].first + ManchetRast(node.sost);
      parent[pair.str] = node.str;
      min_heap.push({dist[pair.str].second, pair.str});
    }
  }
}

void FindDistances(
    std::vector<int>& sost1, Graph& graph,
    std::unordered_map<std::string, std::pair<int, int>>& distances,
    std::unordered_map<std::string, std::string>& parent) {
  std::string first_node = graph.AddNode(sost1);
  distances[first_node] = {0, ManchetRast(sost1)};
  QueueType min_heap;
  min_heap.push({ManchetRast(sost1), first_node});
  parent[first_node] = "0";

  while (!min_heap.empty()) {
    auto dist_node = min_heap.top();
    if (dist_node.second == "123456780") {
      break;
    }
    min_heap.pop();
    if (dist_node.first > distances[dist_node.second].second) {
      continue;
    }
    Expand(graph.sides[dist_node.second], graph, min_heap, distances, parent);
  }
}

int main() {
  BoostIO();
  std::vector<int> sost1(cSize);
  for (int i = 0; i < cSize; ++i) {
    std::cin >> sost1[i];
  }
  if (!HaveAnswer(sost1)) {
    std::cout << "-1";
    return 0;
  }
  Graph graph;
  std::unordered_map<std::string, std::pair<int, int>> distances;
  std::unordered_map<std::string, std::string> parent;

  FindDistances(sost1, graph, distances, parent);

  std::cout << distances["123456780"].first << '\n';
  std::string answer;
  std::vector<int> for_node;
  for (int i = 0; i < cSize; ++i) {
    for_node.push_back(i);
  }
  Node this_node = {for_node, cSize - 1, "123456780"};
  while (parent[this_node.str] != "0") {
    Node prev_node = graph.sides[parent[this_node.str]];
    if (prev_node.pos0 - this_node.pos0 == 3) {
      answer += "U";
    }
    if (prev_node.pos0 - this_node.pos0 == -3) {
      answer += "D";
    }
    if (prev_node.pos0 - this_node.pos0 == 1) {
      answer += "L";
    }
    if (prev_node.pos0 - this_node.pos0 == -1) {
      answer += "R";
    }
    this_node = prev_node;
  }
  std::reverse(answer.begin(), answer.end());
  std::cout << answer;
}
