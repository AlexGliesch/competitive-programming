#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

vector<vector<int>> g;
vector<bool> wake;
map<char, int> index;
int index_ct = 0;
int N, M;

void add(char v) {
  if (index.count(v) == 0)
    index[v] = index_ct++;
}

int main() {
  while (cin >> N >> M) {
    index.clear();
    index_ct = 0;

    char a, b, c;
    cin >> a >> b >> c;
    add(a), add(b), add(c);
    vector<pair<char, char>> edges(M);
    for (int i = 0; i < M; ++i) {
      cin >> edges[i].first >> edges[i].second;
      add(edges[i].first), add(edges[i].second);
    }
    g.clear();
    g.resize(N);
    for (int i = 0; i < M; ++i) {
      g[index[edges[i].first]].push_back(index[edges[i].second]);
      g[index[edges[i].second]].push_back(index[edges[i].first]);
    }
    int yrs = 0, num_wake = 3;
    wake.assign(N, false);
    wake[index[a]] = wake[index[b]] = wake[index[c]] = true;
    vector<int> next_wake;
    while (true) {
      next_wake.clear();
      for (int i = 0; i < N; ++i) {
        if (!wake[i]) {
          int num_wake_connections = 0;
          for (int j = 0; j < g[i].size(); ++j) {
            if (wake[g[i][j]])
              ++num_wake_connections;
          }
          if (num_wake_connections >= 3) {
            next_wake.push_back(i);
          }
        }
      }
      if (next_wake.empty())
        break;
      ++yrs;
      num_wake += next_wake.size();
      for (int i = 0; i < next_wake.size(); ++i)
        wake[next_wake[i]] = true;
    }

    if (num_wake != N)
      cout << "THIS BRAIN NEVER WAKES UP" << endl;
    else
      cout << "WAKE UP IN, " << yrs << ", YEARS" << endl;
  }
}