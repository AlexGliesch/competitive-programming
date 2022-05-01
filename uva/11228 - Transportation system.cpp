#include <algorithm>
#include <ciso646>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>

using namespace std;

/* Gera o grafo completo, e roda MST (Usei Prim). Sempre que adicionar uma
 * aresta
 * com peso maior que r, significa que ela é uma railroad (conecta dois
 * estados).
 * Além disso, o número de estados é o número de railroads + 1.
 *
 * Dei 3 WA por que o g++ não deu warning ao receber um double de uma função
 * em uma variável int. Nota pro futuro: usar -Wall !
 * */

vector<vector<pair<double, int>>> g;
vector<bool> visited;
vector<pair<double, double>> p;
int n, r, num_states;
double cost_roads, cost_railroads;

double dist(const pair<double, double> &a, const pair<double, double> &b) {
  return sqrt((a.first - b.first) * (a.first - b.first) +
              (a.second - b.second) * (a.second - b.second));
}

void prim() {
  priority_queue<pair<double, int>, vector<pair<double, int>>,
                 greater<pair<double, int>>>
      pq;
  visited.assign(n, false);
  visited[0] = true;

  cost_roads = 0, cost_railroads = 0;
  for (int v = 1; v < n; ++v)
    pq.emplace(dist(p[0], p[v]), v);

  while (pq.size()) {
    double w = pq.top().first;
    int u = pq.top().second;
    pq.pop();
    if (visited[u])
      continue;
    visited[u] = true;
    if (w >= r) {
      cost_railroads += w;
      ++num_states;
    } else
      cost_roads += w;
    for (int v = 0; v < n; ++v) {
      if (not visited[v])
        pq.emplace(dist(p[v], p[u]), v);
    }
  }
}

int main() {
  int T;
  cin >> T;
  cout << setprecision(0) << fixed;
  for (int t = 0; t < T; ++t) {
    cin >> n >> r;

    p.clear();
    p.resize(n);
    g.clear();
    g.resize(n);

    for (int i = 0; i < n; ++i) {
      cin >> p[i].first >> p[i].second;
    }

    num_states = 1;
    prim();

    cout << "Case #" << t + 1 << ": " << num_states << ' ' << round(cost_roads)
         << ' ' << round(cost_railroads) << endl;
  }
}