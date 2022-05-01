#include <algorithm>
#include <ciso646>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

/* Just use union-find to add the edges. */

vector<int> pset, size_set;

void init_set(int n) {
  pset.assign(n, 0);
  size_set.assign(n, 1);
  for (int i = 0; i < n; ++i)
    pset[i] = i;
}

int find_set(int i) { return pset[i] == i ? i : (pset[i] = find_set(pset[i])); }

bool is_same_set(int i, int j) { return find_set(i) == find_set(j); }

void union_set(int i, int j) {
  if (is_same_set(i, j))
    return;
  size_set[find_set(j)] += size_set[find_set(i)];
  pset[find_set(i)] = find_set(j);
}

int main() {
  int T;
  cin >> T;
  while (T--) {
    int F;
    cin >> F;
    vector<pair<string, string>> gs;
    map<string, int> name_to_int;
    int n = 0;
    for (int f = 0; f < F; ++f) {
      string sa, sb;
      cin >> sa >> sb;
      if (!name_to_int.count(sa))
        name_to_int[sa] = n++;
      if (!name_to_int.count(sb))
        name_to_int[sb] = n++;
      gs.emplace_back(sa, sb);
    }

    init_set(n);
    for (int i = 0; i < F; ++i) {
      union_set(name_to_int[gs[i].second], name_to_int[gs[i].first]);
      cout << size_set[find_set(name_to_int[gs[i].second])] << endl;
    }
  }
}