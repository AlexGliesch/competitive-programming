#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>

using namespace std;

/*
 * toposort. solve with bfs.
 * start by storing in an array the number of incoming edges in each node,
 * when you read the graph.
 *
 * whenever you visit a node with bfs, decrease the number of incoming edges
 * of each neighbour of that node. if that neighbour turns out to have 0
 * edges, push it on the queue. initially, the queue contains all the nodes
 * that have 0 incoming edges in the input graph.
 *
 * in order to preserve the order, we must use a priority_queue instead of a
 * queue for the bfs. this will enforce that the vertices with lower index
 * be visited first.
 * */

int n, m;
vector<vector<int>> g;
vector<int> in;
map<string, int> name_to_index;
vector<string> index_to_name;

void toposort_bfs() {
  priority_queue<int, vector<int>, greater<int>> pq;
  for (int v = 0; v < n; ++v)
    if (in[v] == 0)
      pq.push(v);
  while (pq.size()) {
    int v = pq.top();
    pq.pop();
    --in[v]; /* decrease so in[v] is -1 and it won't be visited anymore */
    cout << ' ' << index_to_name[v];
    for (auto u : g[v]) {
      if (--in[u] == 0)
        pq.push(u);
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  int num_case = 1;
  while (cin >> n) {
    g.clear();
    g.resize(n);
    in.assign(n, 0);
    name_to_index.clear();
    index_to_name.clear();

    for (int i = 0; i < n; ++i) {
      string s;
      cin >> s;
      name_to_index[s] = i;
      index_to_name.emplace_back(move(s));
    }
    cin >> m;
    for (int i = 0; i < m; ++i) {
      string us, vs;
      cin >> us >> vs;
      int u = name_to_index[us], v = name_to_index[vs];
      ++in[v];
      g[u].push_back(v);
    }
    cout << "Case #" << num_case++
         << ": Dilbert should drink beverages in this order:";
    toposort_bfs();
    cout << '.' << endl << endl;
  }
}