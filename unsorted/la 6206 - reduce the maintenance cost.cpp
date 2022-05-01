#include <cstdio>
#include <vector>
#include <queue>
#include <map>
using namespace std;

typedef long long int lli;

vector<vector<int> > g;
vector<int> bccParent;
vector<lli> bccChildren;
vector<int> ccRoot;

vector<int> dfsStatus;
vector<int> dfsLow;
void processBcc(int n, int parent) {
  bccParent[n] = parent;
  dfsStatus[n] = 2;
  for (int c : g[n])
    if (c != parent && dfsStatus[c] == 1) {
      processBcc(c, -1);
      bccChildren[n] += bccChildren[c];
    }
}
int tarjanDfs(int n, int root, int id=0, int parent=-1) {
  dfsStatus[n] = 1;
  dfsLow[n] = id;
  ccRoot[n] = root;
  int nextId = id+1;
  for (int c : g[n])
    if (c != parent) {
      if (dfsStatus[c] == 0)
        nextId = tarjanDfs(c, root, nextId, n);
      if (dfsStatus[c] == 1)
        dfsLow[n] = min(dfsLow[n], dfsLow[c]);
  }
  if (dfsLow[n] == id) {
    processBcc(n, parent);
    if (parent != -1)
      bccChildren[parent] += bccChildren[n];
  }
  return nextId;
}

int main() {
  int t;
  scanf("%d", &t);
  for (int ta=0; ta<t; ++ta) {
    int n, m;
    scanf("%d %d", &n, &m);
    g.assign(n, {});
    bccParent.resize(n);
    bccChildren.assign(n, 1);
    dfsStatus.assign(n, 0);
    dfsLow.resize(n);
    ccRoot.assign(n, -1);
    vector<lli> cost(n);
    for (int i=0; i<n; ++i)
      scanf("%lld", &(cost[i]));
    vector<map<int, lli> > w(n);
    for (int i=0; i<m; ++i) {
      int u, v, wr;
      scanf("%d %d %d", &u, &v, &wr);
      u--; v--;
      g[u].push_back(v);
      g[v].push_back(u);
      w[u][v] = wr;
      w[v][u] = wr;
    }
    for (int i=0; i<n; ++i)
      if (dfsStatus[i] == 0)
        tarjanDfs(i, i);
    for (int i=0; i<n; ++i)
      if (bccParent[i] != -1)
        cost[i] += w[i][bccParent[i]]*bccChildren[i]*(bccChildren[ccRoot[i]]-bccChildren[i]);
    priority_queue<pair<lli, int> > pq;
    for (int i=0; i<n; ++i)
      pq.push({cost[i], i});
    lli best = pq.top().first;
    while (!pq.empty()) {
      int i = pq.top().second;
      lli c = pq.top().first;
      best = min(best, c);
      pq.pop();
      if (c != cost[i])
        continue;
      if (bccParent[i] == -1)
        break;
      lli edge = w[i][bccParent[i]]*bccChildren[i]*(bccChildren[ccRoot[i]]-bccChildren[i]);
      cost[bccParent[i]] += edge;
      cost[i] -= edge;
      pq.push({cost[bccParent[i]], bccParent[i]});
      pq.push({cost[i], i});
      bccParent[i] = -1;
    }
    printf("Case %d: %lld\n", ta+1, best);
  }
}