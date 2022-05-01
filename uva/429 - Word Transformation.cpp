#include <algorithm>
#include <ciso646>
#include <iostream>
#include <map>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

map<string, vector<string>> g;

bool is_neighbour(const string &a, const string &b) {
  if (a.size() != b.size())
    return false;
  int num_diff = 0;
  for (unsigned i = 0; i < a.size(); ++i) {
    if (a[i] != b[i])
      ++num_diff;
    if (num_diff > 1)
      return false;
  }
  return num_diff == 1;
}

int bfs(const string &s, const string &t) {
  queue<string> q;
  map<string, int> dist;
  dist[s] = 0;
  q.push(s);
  while (q.size()) {
    const auto &v = q.front();
    q.pop();
    if (v == t)
      return dist[t];
    for (auto &u : g[v]) {
      if (dist.count(u) == 0) {
        dist[u] = 1 + dist[v];
        q.push(u);
      }
    }
  }
  return -1;
}

int main() {
  int T;
  cin >> T;
  for (int t = 0; t < T; ++t) {
    if (t)
      cout << endl;
    string buf;
    while (cin >> buf and buf != "*") {
      g.emplace(buf, vector<string>());
    }
    for (auto &a : g)
      for (auto &b : g) {
        if (a.first != b.first and is_neighbour(a.first, b.first)) {
          a.second.push_back(b.first);
          b.second.push_back(a.first);
        }
      }
    getline(cin, buf);
    while (getline(cin, buf) and buf.size()) {
      istringstream ss(buf);
      string a, b;
      ss >> a >> b;
      cout << a << ' ' << b << ' ' << bfs(a, b) << endl;
    }
  }
}