#include <algorithm>
#include <ciso646>
#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

struct RMQ {
  vector<ll> A;
  vector<vector<ll>> spt;

  void build(vector<ll> v) {
    A = move(v);
    spt.resize(A.size(), vector<ll>(1 + (ll)ceil(log2(double(A.size())))));
    for (ll i = 0; i < A.size(); ++i) {
      spt[i][0] = i;
    }

    /* the two nested loops below have overall time complexity = O(n log n) */
    for (ll j = 1; (1 << j) <= A.size(); ++j) {
      for (ll i = 0; i + (1 << j) - 1 < A.size(); ++i) {
        if (A[spt[i][j - 1]] < A[spt[i + (1 << (j - 1))][j - 1]]) {
          spt[i][j] = spt[i][j - 1];
        } else {
          spt[i][j] = spt[i + (1 << (j - 1))][j - 1];
        }
      }
    }
  }

  ll query(ll i, ll j) {
    ll k = (ll)floor(log((double)(j - i + 1)) / log(2.0));
    if (A[spt[i][k]] <= A[spt[j - (1 << k) + 1][k]]) {
      return spt[i][k];
    } else {
      return spt[j - (1 << k) + 1][k];
    }
  }
};

struct LCA {
private:
  vector<ll> L, E, H;
  const vector<vector<ll>> &g;
  ll idx;
  RMQ rmq;

  void dfs(ll cur, ll depth, ll prev) {
    H[cur] = idx;
    E[idx] = cur;
    L[idx++] = depth;
    for (ll i = 0; i < g[cur].size(); ++i) {
      if (g[cur][i] == prev)
        continue;
      dfs(g[cur][i], depth + 1, cur);
      E[idx] = cur;
      L[idx++] = depth;
    }
  }

public:
  LCA(const vector<vector<ll>> &g)
      : g(g), L(2 * g.size()), E(2 * g.size()), H(g.size(), -1), idx(0) {
    dfs(0, 0, -1);
    rmq.build(L);
  }

  /* returns the index of the lowest common ancestor between u and v */
  ll lca(ll u, ll v) {
    if (H[u] >= H[v])
      swap(u, v);
    return E[rmq.query(H[u], H[v])];
  }

  /* returns the depth (from root = 0) of vertex v */
  ll depth(ll v) { return L[v]; }
};

void dfs_cost(const vector<vector<ll>> &g, const vector<vector<ll>> &cost,
              vector<ll> &dist, ll v, ll d, ll prev) {
  dist[v] = d;
  for (ll i = 0; i < g[v].size(); ++i) {
    if (g[v][i] == prev)
      continue;
    dfs_cost(g, cost, dist, g[v][i], d + cost[v][i], v);
  }
}

int main() {
  ll N;
  ios_base::sync_with_stdio(false);
  while (cin >> N, N) {
    vector<vector<ll>> g(N);
    vector<vector<ll>> cost(N);
    for (ll i = 1; i <= N - 1; ++i) {
      ll Ai, Li;
      cin >> Ai >> Li;
      g[i].push_back(Ai);
      g[Ai].push_back(i);
      cost[i].push_back(Li);
      cost[Ai].push_back(Li);
    }

    vector<ll> dist_0(N);
    dfs_cost(g, cost, dist_0, 0, 0, -1);

    LCA lca(g);

    ll Q;
    cin >> Q;
    for (ll i = 0; i < Q; ++i) {
      ll S, T;
      cin >> S >> T;
      if (i)
        cout << " ";
      cout << dist_0[S] + dist_0[T] - 2 * dist_0[lca.lca(S, T)];
    }
    cout << endl;
  }
}