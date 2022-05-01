#include <algorithm>
#include <ciso646>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

/*
 * find all pairs shortest paths using floyd-warshall algorithm (which
 * is O(n^3)), and divide by the possible number of pairs (n * (n-1)), where n
 * is the number of vertices on the graph.
 *
 * floyd-warshall is a DP algorithm, where we use the distance to intermediate
 * vertices to find the distance between any two vertices.
 * i.e., the distance from i to j, dist(i, j), is the minimum of
 * dist(i, k) + dist(k, j) for every vertex k. the algorithm only works if we
 * let vertices be used as intermediates only one at a time.
 *
 * don't forget that you cannot initialize the adjacency matrix with too big
 * values, otherwise floyd-warshall will overflow and the results will be
 * wrong.
 *
 * important for this problem:
 * even though the labels can be from 1 to 100, any arbitrary subset of those
 * numbers may be used. for instance, it can eb that only 1, 2, 73 and 99 are
 * used. so, you must somehow mark which numbers were used; for that, i set
 * that if k is used, g[k][k] = 0, otherwise, = INF.
 * */

int main() {
  ios_base::sync_with_stdio(false);
  int a, b, t = 0;
  string buf;
  while (getline(cin, buf)) {
    vector<vector<int>> g(110, vector<int>(110, (1 << 20)));

    istringstream ss(buf);
    int n = 0, used = 0;
    do {
      ss >> a >> b;
      g[a][b] = 1;
      g[a][a] = g[b][b] = 0;
      n = max(n, max(a, b));
    } while (not(a == 0 and b == 0));

    if (n == 0)
      break;

    /* floyd-warshall algorithm */
    for (int k = 1; k <= n; ++k)
      for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
          g[i][j] = min(g[i][j], g[i][k] + g[k][j]);

    double avg = 0;
    for (int i = 1; i <= n; ++i) {
      if (g[i][i] != 0)
        continue;
      ++used;
      for (int j = 1; j <= n; ++j)
        if (g[j][j] == 0)
          avg += g[i][j];
    }
    avg /= double(used * (used - 1));
    cout << "Case " << ++t
         << ": average length between pages = " << setprecision(3) << fixed
         << avg << " clicks" << endl;
  }
}