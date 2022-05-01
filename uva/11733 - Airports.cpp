#include <algorithm>
#include <ciso646>
#include <iostream>
#include <tuple>
#include <vector>

using namespace std;

/*
 * kruskal's algorithm for MST. implemented it using union-find disjoint sets
 * data structure. if you need a more thorough explanation on kruskal's
 * algorithm, look on your book.
 *
 * for this problem, we cannot add an edge of the cost of adding that edge
 * is bigger than the cost of an airport (because it would be cheaper to build
 * an airport on that node, instead of connecting it to the rest). the number
 * of sets (connected components) that the algorithm ends with is the number
 * of airports.
 *
 * another solution would be to run prim's, and only add edges whose cost is
 * less than building an airport, and, after running prim's, perform dfs's to
 * count the number of connected components (= number of airports).
 * */

vector<tuple<int, int, int>> g;
vector<int> pset;
int n, m, a, T;

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
  cin >> T;
  for (int t = 1; t <= T; ++t) {
    cin >> n >> m >> a;
    g.clear();
    for (int i = 0; i < m; ++i) {
      int x, y, c;
      cin >> x >> y >> c;
      g.emplace_back(c, x - 1, y - 1);
    }

    sort(begin(g), end(g));
    init_set(n);

    int cost = 0;
    int num_airports = n;

    /* kruskal's algorithm: */
    for (int i = 0; i < m; ++i) {
      int w = get<0>(g[i]), u = get<1>(g[i]), v = get<2>(g[i]);
      /* if cost of building road e > cost of building airport,
       * we're done.*/
      if (w >= a)
        break;
      /* join sets. */
      if (not is_same_set(u, v)) {
        cost += w;
        union_set(u, v);
        --num_airports;
      }
    }

    cost += a * num_airports;
    cout << "Case #" << t << ": " << cost << " " << num_airports << endl;
  }
}