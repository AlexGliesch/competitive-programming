#include <algorithm>
#include <ciso646>
#include <iostream>
#include <tuple>
#include <vector>

using namespace std;

vector<tuple<int, int, int>> g;
vector<int> pset;
int n, m;

void init_set(int n) {
  pset.assign(n, 0);
  for (int i = 0; i < n; ++i)
    pset[i] = i;
}

int find_set(int i) { return pset[i] == i ? i : (pset[i] = find_set(pset[i])); }

bool is_same_set(int i, int j) { return find_set(i) == find_set(j); }

void union_set(int i, int j) {
  if (is_same_set(i, j))
    return;
  pset[find_set(i)] = find_set(j);
}

int main() {
  while (cin >> n >> m, n != 0 and m != 0) {
    g.clear();
    for (int i = 0; i < m; ++i) {
      int u, v, w;
      cin >> u >> v >> w;
      g.emplace_back(w, u, v);
    }

    sort(begin(g), end(g));
    init_set(n);

    bool has_cycle = false;
    for (int i = 0; i < m; ++i) {
      auto e = g[i];
      if (not is_same_set(get<1>(e), get<2>(e))) {
        union_set(get<1>(e), get<2>(e));
      } else {
        if (has_cycle)
          cout << ' ';
        cout << get<0>(e);
        has_cycle = true;
      }
    }

    if (not has_cycle)
      cout << "forest";
    cout << endl;
  }
}