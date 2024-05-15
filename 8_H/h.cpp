// В задаче необходимо найти решение восьминашек

#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

const int cSize = 9;
const std::string cFindString = "123456780";
const std::vector<int> cFindState = {1, 2, 3, 4, 5, 6, 7, 8, 0};

void BoostIO() {
  std::ios::sync_with_stdio(false);
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

struct Node {
  std::vector<int> state;
  int pos0;
  std::string str_state;
};

class Graph {
 public:
  std::unordered_map<std::string, Node> sides;
  explicit Graph() = default;

  std::string AddNode(std::vector<int> state) {
    std::string str_state;
    int pos0;
    for (int i = 0; i < cSize; ++i) {
      str_state += static_cast<char>(state[i] + '0');
      if (state[i] == 0) {
        pos0 = i;
      }
    }
    sides[str_state] = Node({state, pos0, str_state});
    return str_state;
  }
};

std::vector<Node> NextPositions(Node node) {
  const int cDown = 6;
  std::vector<Node> next_states;

  if (node.pos0 > 2) {
    std::vector<int> new_state = node.state;
    std::swap(new_state[node.pos0], new_state[node.pos0 - 3]);
    std::string str;
    for (int i = 0; i < cSize; ++i) {
      str += static_cast<char>(new_state[i] + '0');
    }
    next_states.push_back({new_state, node.pos0 - 3, str});
  }

  if (node.pos0 < cDown) {
    std::vector<int> new_state = node.state;
    std::swap(new_state[node.pos0], new_state[node.pos0 + 3]);
    std::string str;
    for (int i = 0; i < cSize; ++i) {
      str += static_cast<char>(new_state[i] + '0');
    }
    next_states.push_back({new_state, node.pos0 + 3, str});
  }

  if (node.pos0 % 3 != 0) {
    std::vector<int> new_state = node.state;
    std::swap(new_state[node.pos0], new_state[node.pos0 - 1]);
    std::string str;
    for (int i = 0; i < cSize; ++i) {
      str += static_cast<char>(new_state[i] + '0');
    }
    next_states.push_back({new_state, node.pos0 - 1, str});
  }

  if (node.pos0 % 3 != 2) {
    std::vector<int> new_state = node.state;
    std::swap(new_state[node.pos0], new_state[node.pos0 + 1]);
    std::string str;
    for (int i = 0; i < cSize; ++i) {
      str += static_cast<char>(new_state[i] + '0');
    }
    next_states.push_back({new_state, node.pos0 + 1, str});
  }
  return next_states;
}

bool HaveAnswer(std::vector<int> state) {
  int count_inversions = 0;
  for (int i = 0; i < cSize; ++i) {
    for (int j = i + 1; j < cSize; ++j) {
      if (state[i] != 0 and state[j] != 0 and state[i] > state[j]) {
        count_inversions += 1;
      }
    }
  }
  return count_inversions % 2 == 0;
}

using QueueType = std::priority_queue<std::pair<int, std::string>,
                                      std::vector<std::pair<int, std::string>>,
                                      std::greater<>>;

int ManhattanDist(std::vector<int> state) {
  int dist = 0;
  for (int i = 0; i < cSize; ++i) {
    if (state[i] == 0) {
      continue;
    }
    int str_v = (state[i] - 1) / 3;
    int col_v = (state[i] - 1) % 3;
    dist += abs(str_v - (i / 3)) + abs(col_v - (i % 3));
  }
  return dist;
}

void Expand(Node& node, Graph& graph, QueueType& min_heap,
            std::unordered_map<std::string, std::pair<int, int>>& dist,
            std::unordered_map<std::string, std::string>& parent) {
  for (const auto& pair : NextPositions(node)) {
    graph.AddNode(pair.state);

    if (!dist.contains(pair.str_state) or
        dist[pair.str_state].first > dist[node.str_state].first + 1) {
      dist[pair.str_state].first = dist[node.str_state].first + 1;
      dist[pair.str_state].second =
          dist[node.str_state].first + ManhattanDist(node.state);
      parent[pair.str_state] = node.str_state;
      min_heap.push({dist[pair.str_state].second, pair.str_state});
    }
  }
}

void FindDistances(
    std::vector<int>& state, Graph& graph,
    std::unordered_map<std::string, std::pair<int, int>>& distances,
    std::unordered_map<std::string, std::string>& parent) {
  std::string first_node = graph.AddNode(state);
  distances[first_node] = {0, ManhattanDist(state)};
  QueueType min_heap;
  min_heap.push({ManhattanDist(state), first_node});
  parent[first_node] = "0";

  while (!min_heap.empty()) {
    auto dist_node = min_heap.top();
    if (dist_node.second == cFindString) {
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
  std::vector<int> state(cSize);
  for (int i = 0; i < cSize; ++i) {
    std::cin >> state[i];
  }

  if (!HaveAnswer(state)) {
    std::cout << "-1";
    return 0;
  }
  Graph graph;
  std::unordered_map<std::string, std::pair<int, int>> distances;
  std::unordered_map<std::string, std::string> parent;

  FindDistances(state, graph, distances, parent);

  std::cout << distances[cFindString].first << '\n';
  std::string shifts_for_win;

  Node this_node = {cFindState, cSize - 1, cFindString};
  while (parent[this_node.str_state] != "0") {
    Node prev_node = graph.sides[parent[this_node.str_state]];
    if (prev_node.pos0 - this_node.pos0 == 3) {
      shifts_for_win += "U";
    }
    if (prev_node.pos0 - this_node.pos0 == -3) {
      shifts_for_win += "D";
    }
    if (prev_node.pos0 - this_node.pos0 == 1) {
      shifts_for_win += "L";
    }
    if (prev_node.pos0 - this_node.pos0 == -1) {
      shifts_for_win += "R";
    }
    this_node = prev_node;
  }
  std::reverse(shifts_for_win.begin(), shifts_for_win.end());
  std::cout << shifts_for_win;
}
