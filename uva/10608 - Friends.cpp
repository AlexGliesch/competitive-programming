#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

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
    int N, M;
    cin >> N >> M;
    init_set(N);
    for (int i = 0; i < M; ++i) {
      int x, y;
      cin >> x >> y;
      --x, --y;
      union_set(x, y);
    }
    cout << *max_element(size_set.begin(), size_set.end()) << endl;
  }
}
