#include <algorithm>
#include <cmath>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <queue>

using namespace std;

int n;
double pt[100][2];
bool taken[100];

double dist(int a, int b) {
  return sqrt((pt[a][0] - pt[b][0]) * (pt[a][0] - pt[b][0]) +
              (pt[a][1] - pt[b][1]) * (pt[a][1] - pt[b][1]));
}

double prim() {
  memset(taken, false, sizeof taken);
  priority_queue<pair<double, int>, vector<pair<double, int>>,
                 greater<pair<double, int>>>
      pq;
  double cost = 0;
  taken[0] = true;

  for (int v = 1; v < n; ++v)
    pq.push(make_pair(dist(0, v), v));

  while (pq.size()) {
    int u = pq.top().second;
    double w = pq.top().first;
    pq.pop();
    if (taken[u])
      continue;
    taken[u] = true;
    cost += w;
    for (int v = 0; v < n; ++v) {
      if (!taken[v])
        pq.push(make_pair(dist(u, v), v));
    }
  }
  return cost;
}

int main() {
  int t;
  cin >> t;
  for (int k = 0; k < t; ++k) {
    cin >> n;
    for (int i = 0; i < n; ++i) {
      cin >> pt[i][0] >> pt[i][1];
    }
    if (k > 0)
      cout << endl;
    cout << setprecision(2) << fixed << prim() << endl;
  }
}