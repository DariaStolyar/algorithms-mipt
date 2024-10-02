 #include <algorithm>
#include <climits>
#include <iostream>
#include <queue>
#include <vector>

const int cCodeA = 97;
const int cCountLetters = 26;

struct Node {
  std::vector<int> to;
  int term;
  Node() {
    to.resize(cCountLetters, -1);
    term = -1;
  }

  void AddEdge(char symbol, int node) { to[symbol - cCodeA] = node; }
};

struct Bor {
  std::vector<Node*> nodes;

  Bor() { nodes.push_back(new Node()); }

  int AddString(std::string& string, int number) {
    int node = 0;
    for (size_t i = 0; i < string.size(); ++i) {
      if (nodes[node]->to[string[i] - cCodeA] == -1) {
        nodes[node]->to[string[i] - cCodeA] = nodes.size();
        nodes.push_back(new Node());
      }
      node = nodes[node]->to[string[i] - cCodeA];
    }
    if (nodes[node]->term == -1) {
      nodes[node]->term = number;
    }
    return nodes[node]->term;
  }

  void CheckString(std::string& string, std::vector<std::pair<int, int>>& ans,
                   int number, bool equal) {
    int node = 0;
    for (size_t i = 0; i < string.size(); ++i) {
      if (nodes[node]->to[string[i] - cCodeA] == -1) {
        return;
      }
      node = nodes[node]->to[string[i] - cCodeA];
      if (number != nodes[node]->term and nodes[node]->term != -1 and
          (i != string.size() - 1 or equal)) {
        bool palindrom = true;
        for (size_t j = i + 1; j < string.size(); ++j) {
          if (string[j] != string[string.size() - j + i]) {
            palindrom = false;
            break;
          }
        }
        if (palindrom and !equal) {
          ans.push_back({number, nodes[node]->term});
        } else if (palindrom) {
          ans.push_back({nodes[node]->term, number});
        }
      }
    }
  }

  int Size() const { return nodes.size(); }

  bool HaveEdge(int node, int symbol) { return nodes[node]->to[symbol] != -1; }

  int ToNode(int node, int symbol) { return nodes[node]->to[symbol]; }

  bool Term(int node) { return nodes[node]->term != -1; }

  int Number(int node) { return nodes[node]->term; }

  ~Bor() {
    for (auto* node : nodes) {
      delete node;
    }
  }
};

void PrepareIO() {
  std::ios::sync_with_stdio(false);
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
}

int main() {
  PrepareIO();

  Bor bor;
  Bor bor_r;
  int count;
  std::cin >> count;
  std::vector<std::string> right(count);
  std::vector<std::string> reversed(count);

  for (int i = 0; i < count; ++i) {
    std::string new_str;
    std::cin >> new_str;
    bor.AddString(new_str, i);
    right[i] = new_str;
    std::string rev;
    for (int j = new_str.size() - 1; j >= 0; --j) {
      rev += new_str[j];
    }
    bor_r.AddString(rev, i);
    reversed[i] = rev;
  }

  std::vector<std::pair<int, int>> ans;

  for (int i = 0; i < count; ++i) {
    bor.CheckString(reversed[i], ans, i, true);
    bor_r.CheckString(right[i], ans, i, false);
  }

  std::cout << ans.size() << "\n";
  for (size_t i = 0; i < ans.size(); ++i) {
    std::cout << ans[i].first + 1 << " " << ans[i].second + 1 << "\n";
  }
}
