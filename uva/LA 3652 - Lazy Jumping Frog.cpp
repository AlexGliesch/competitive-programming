#include <algorithm>
#include <ciso646>
#include <cstring>
#include <iostream>
#include <queue>

using namespace std;

/* dijkstra. */

int cal[5][5] = {{7, 6, 5, 6, 7},
                 {6, 3, 2, 3, 6},
                 {5, 2, 0, 2, 5},
                 {6, 3, 2, 3, 6},
                 {7, 6, 5, 6, 7}};

struct Edge {
  Edge(int r, int c, int cost) : r(r), c(c), cost(cost) {}
  int r, c, cost;
  bool operator<(const Edge &e) const { return cost > e.cost; }
};

bool water[1010][1010];
int dist[1010][1010];
int C, R, Cf, Rf, Ct, Rt;

int dijkstra() {
  priority_queue<Edge> pq;
  pq.push(Edge(Rf, Cf, 0));
  memset(dist, -1, sizeof dist);
  dist[Rf][Cf] = 0;

  while (not pq.empty()) {
    Edge e = pq.top();
    pq.pop();
    if (e.cost != dist[e.r][e.c])
      continue;

    for (int i = max(0, e.r - 2); i <= min(R - 1, e.r + 2); i++) {
      for (int j = max(0, e.c - 2); j <= min(C - 1, e.c + 2); ++j) {
        if (water[i][j] or (i == e.r and j == e.c))
          continue;
        int d = dist[e.r][e.c] + cal[i - e.r + 2][j - e.c + 2];
        if (dist[i][j] == -1 or dist[i][j] > d) {
          dist[i][j] = d;
          pq.push(Edge(i, j, d));
        }
      }
    }
  }
  return dist[Rt][Ct];
}

int main() {
  while (true) {
    cin >> C >> R;
    if (C == 0 and R == 0)
      break;

    cin >> Cf >> Rf >> Ct >> Rt;
    --Cf, --Rf, --Ct, --Rt;

    memset(water, false, sizeof water);
    int W;
    cin >> W;

    for (int i = 0; i < W; ++i) {
      int c1, r1, c2, r2;
      cin >> c1 >> r1 >> c2 >> r2;
      for (int r = r1 - 1; r <= r2 - 1; ++r)
        for (int c = c1 - 1; c <= c2 - 1; ++c)
          water[r][c] = true;
    }

    int val = dijkstra();
    if (val == -1)
      cout << "impossible" << endl;
    else
      cout << val << endl;
  }
}