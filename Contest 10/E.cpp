#include <algorithm>
#include <climits>
#include <iostream>
#include <map>
#include <queue>
#include <vector>

struct Node {
  std::map<std::string, int> to;
  int count_term;
  Node() { count_term = 0; }
  void AddEdge(std::string symbol, int node) { to[symbol] = node; }
};

struct Bor {
  std::vector<Node*> nodes;

  Bor() { nodes.push_back(new Node()); }

  void AddString(std::string& string) {
    int node = 0;
    nodes[node]->count_term += 1;
    for (size_t i = 0; i < string.size(); ++i) {
      std::string two;
      two += string[i];
      two += string[string.size() - i - 1];
      if (nodes[node]->to.find(two) == nodes[node]->to.end()) {
        nodes[node]->to[two] = nodes.size();
        nodes.push_back(new Node());
      }
      node = nodes[node]->to[two];
      nodes[node]->count_term += 1;
    }
  }

  int Size() const { return nodes.size(); }

  bool HaveEdge(int node, std::string symbol) {
    return nodes[node]->to[symbol] != -1;
  }

  int ToNode(int node, std::string symbol) { return nodes[node]->to[symbol]; }

  int CountTerm(int node) { return nodes[node]->count_term; }

  ~Bor() {
    for (auto* node : nodes) {
      delete node;
    }
  }
};

void DFS(int node, Bor& bor, std::pair<int, int>& num_height,
         std::vector<int>& queries, std::vector<int>& ans_vec) {
  int num = num_height.first;
  int height = num_height.second;
  if (bor.CountTerm(node) >= num) {
    for (size_t i = 0; i < queries.size(); ++i) {
      if (queries[i] == height) {
        ans_vec[i] += 1;
      }
    }
  }
  for (const auto& [key, value] : bor.nodes[node]->to) {
    if (bor.CountTerm(value) >= num) {
      std::pair<int, int> pair = {num, height + 1};
      DFS(value, bor, pair, queries, ans_vec);
    }
  }
}

void PrepareIO() {
  std::ios::sync_with_stdio(false);
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

int main() {
  PrepareIO();

  Bor bor;
  int count_str;
  int num;
  std::cin >> count_str >> num;

  for (int i = 0; i < count_str; ++i) {
    std::string new_str;
    std::cin >> new_str;
    bor.AddString(new_str);
  }

  int count_request;
  std::cin >> count_request;
  std::vector<int> queries(count_request);
  std::vector<int> ans_vec(count_request, 0);
  for (int i = 0; i < count_request; ++i) {
    int request;
    std::cin >> request;
    queries[i] = request;
  }
  std::pair<int, int> pair = {num, 0};
  DFS(0, bor, pair, queries, ans_vec);
  for (int i = 0; i < count_request; ++i) {
    std::cout << ans_vec[i] << "\n";
  }
}
