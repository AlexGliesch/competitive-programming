#include <cmath>
#include <vector>
#include <iostream>
#include <queue>

using namespace std;

struct Edge {
  int from, to, cap, flow, index;
  Edge(int from, int to, int cap, int flow, int index)
      : from(from), to(to), cap(cap), flow(flow), index(index) {}
};
struct PushRelabel {
  int N;
  vector<vector<Edge>> G;
  vector<int> excess;
  vector<int> dist, active, count;
  queue<int> Q;
  PushRelabel(int N) : N(N), G(N), excess(N), dist(N), active(N), count(2 * N) {}
  void AddEdge(int from, int to, int cap) {
    G[from].emplace_back(from, to, cap, 0, G[to].size());
    if (from == to) G[from].back().index++;
    G[to].emplace_back(to, from, 0, 0, G[from].size() - 1);
  }
  void Enqueue(int v) {
    if (!active[v] && excess[v] > 0) {
      active[v] = true;
      Q.push(v);
    }
  }
  void Push(Edge& e) {
    int amt = int(min(excess[e.from], int(e.cap - e.flow)));
    if (dist[e.from] <= dist[e.to] || amt == 0) return;
    e.flow += amt;
    G[e.to][e.index].flow -= amt;
    excess[e.to] += amt;
    excess[e.from] -= amt;
    Enqueue(e.to);
  }
  void Gap(int k) {
    for (int v = 0; v < N; v++) {
      if (dist[v] < k) continue;
      count[dist[v]]--;
      dist[v] = max(dist[v], N + 1);
      count[dist[v]]++;
      Enqueue(v);
    }
  }
  void Relabel(int v) {
    count[dist[v]]--;
    dist[v] = 2 * N;
    for (int i = 0; i < G[v].size(); i++)
      if (G[v][i].cap - G[v][i].flow > 0) dist[v] = min(dist[v], dist[G[v][i].to] + 1);
    count[dist[v]]++;
    Enqueue(v);
  }
  void Discharge(int v) {
    for (int i = 0; excess[v] > 0 && i < G[v].size(); i++)
      Push(G[v][i]);
    if (excess[v] > 0) {
      if (count[dist[v]] == 1)
        Gap(dist[v]);
      else
        Relabel(v);
    }
  }
  int GetMaxFlow(int s, int t) {
    count[0] = N - 1;
    count[N] = 1;
    dist[s] = N;
    active[s] = active[t] = true;
    for (int i = 0; i < G[s].size(); i++) {
      excess[s] += G[s][i].cap;
      Push(G[s][i]);
    }
    while (!Q.empty()) {
      int v = Q.front();
      Q.pop();
      active[v] = false;
      Discharge(v);
    }
    int totflow = 0;
    for (int i = 0; i < G[s].size(); i++)
      totflow += G[s][i].flow;
    return totflow;
  }
};

int main() {
  int h, w, c;
  scanf("%d%d%d", &h, &w, &c);
  const int n = 3 + h + w;
#define SOURCE 0
#define SINK 1
#define EMPLOYEE(i) ((i) + 2)
#define DAY(i) ((i) + 2 + w)
  PushRelabel pr(n);
  // Connect source and each employee w/ cap c
  for (int i = 0; i < w; ++i) {
    pr.AddEdge(SOURCE, EMPLOYEE(i), c);
  }
  // Connect each day and sink w/ cap 1
  for (int i = 0; i < h; ++i) {
    pr.AddEdge(DAY(i), SINK, 1);
  }
  // Connect employees and days w/ cap 1
  for (int i = 0; i < w; ++i) {
    int r;
    scanf("%d", &r);
    for (int j = 0; j < r; ++j) {
      int mj;
      scanf("%d", &mj);
      pr.AddEdge(EMPLOYEE(i), DAY(mj), 1);
    }
  }
  const int flow = pr.GetMaxFlow(SOURCE, SINK);
  if (flow == h) {
    printf("yes\n");
  } else {
    printf("no\n");
  }
}