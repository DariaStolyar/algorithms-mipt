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

void CreateLinkAndStep(Bor& bor, std::vector<int>& link,
                       std::vector<int>& compressed,
                       std::vector<std::vector<int>>& step) {
  step.resize(bor.Size(), std::vector<int>(cCountLetters));
  link.resize(bor.Size());
  compressed.resize(bor.Size(), -1);
  std::queue<int> queue;
  for (int s = 0; s < cCountLetters; ++s) {
    if (bor.HaveEdge(0, s)) {
      step[0][s] = bor.ToNode(0, s);
    } else {
      step[0][s] = 0;
    }
  }
  queue.push(0);
  while (!queue.empty()) {
    int node = queue.front();
    queue.pop();
    for (int s = 0; s < cCountLetters; ++s) {
      if (!bor.HaveEdge(node, s)) {
        continue;
      }
      int child = bor.ToNode(node, s);
      link[child] = (node == 0 ? 0 : step[link[node]][s]);
      compressed[child] =
          (bor.Term(link[child]) ? link[child] : compressed[link[child]]);
      for (int d = 0; d < cCountLetters; ++d) {
        step[child][d] = (bor.HaveEdge(child, d) ? bor.ToNode(child, d)
                                                 : step[link[child]][d]);
      }
      queue.push(child);
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

  std::string str;
  std::cin >> str;

  Bor bor;
  int count;
  std::cin >> count;
  std::vector<int> len_string(count);
  std::vector<int> numbers(count);
  for (int i = 0; i < count; ++i) {
    std::string new_str;
    std::cin >> new_str;
    len_string[i] = new_str.size();
    numbers[i] = bor.AddString(new_str, i);
  }

  std::vector<std::vector<int>> ans(count, std::vector<int>());
  std::vector<int> link;
  std::vector<int> compressed;
  std::vector<std::vector<int>> step;
  CreateLinkAndStep(bor, link, compressed, step);
  int suff = 0;
  for (int i = 0; i < static_cast<int>(str.size()); ++i) {
    suff = step[suff][str[i] - cCodeA];
    if (bor.Term(suff)) {
      ans[bor.Number(suff)].push_back(i + 2 - len_string[bor.Number(suff)]);
    }
    int t = compressed[suff];
    while (t != -1 and t != 0) {
      ans[bor.Number(t)].push_back(i + 2 - len_string[bor.Number(t)]);
      t = compressed[t];
    }
  }
  for (size_t i = 0; i < ans.size(); ++i) {
    std::cout << ans[numbers[i]].size() << " ";
    for (size_t j = 0; j < ans[numbers[i]].size(); ++j) {
      std::cout << ans[numbers[i]][j] << " ";
    }
    std::cout << "\n";
  }
}
