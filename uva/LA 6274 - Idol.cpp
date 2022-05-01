#include <algorithm>
#include <ciso646>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

/* 2-satisfability problem. Solvable with Kosaraju's SCC: create a graph
 * that has 2n vertices, where n is the number of variables. The first n
 * correspond to the 'true' literal, the second half are the negation literal.
 * For each clause (a V b), add edge ~a - b and ~b - a. Find SCC; if for any
 * vertex a and !a are in the same component, then it is not satisfiable.
 * To make sure that variable a is true, make sure ~a can reach a
 * in the graph.
 * */

int n, m, N;
vector<vector<int>> g, g_t;
vector<int> comp, s;
vector<bool> visited;
int num_scc;

void dfs1(int v) {
  if (visited[v])
    return;
  visited[v] = true;
  for (int i = 0; i < g[v].size(); ++i)
    dfs1(g[v][i]);
  s.push_back(v);
}

void dfs2(int v) {
  if (visited[v])
    return;
  visited[v] = true;
  comp[v] = num_scc;
  for (int i = 0; i < g_t[v].size(); ++i)
    dfs2(g_t[v][i]);
}

void kosaraju() {
  num_scc = 0;
  s.clear();
  comp.assign(N, 0);
  visited.assign(N, false);

  for (int v = 0; v < N; ++v)
    dfs1(v);

  visited.assign(N, false);
  for (int i = s.size() - 1; i >= 0; --i) {
    if (!visited[s[i]]) {
      dfs2(s[i]);
      ++num_scc;
    }
  }
}

int main() {
  while (cin >> n >> m and n != 0 and m != 0) {
    N = 2 * n + 20;
    g.clear();
    g.resize(N);
    g_t.clear();
    g_t.resize(N);
    for (int i = 0; i < m; ++i) {
      int x, y;
      cin >> x >> y;
      g[-x + n].push_back(y + n);
      g[-y + n].push_back(x + n);
      g_t[x + n].push_back(-y + n);
      g_t[y + n].push_back(-x + n);
    }

    kosaraju();
    bool yes = true;
    for (int i = 1; i <= n; ++i) {
      if (comp[i + n] == comp[-i + n]) {
        yes = false;
        break;
      }
    }
    if (yes) {
      /* If there is a path from ~L1 to L1 then L1 is true.
       * (not sure exactly why) */
      visited.assign(N, false);
      dfs2(-1 + n);
      if (visited[1 + n])
        yes = false;
    }

    if (yes)
      cout << "yes" << endl;
    else
      cout << "no" << endl;
  }
}