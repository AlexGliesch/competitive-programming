#include <iostream>
#include <queue>
#include <vector>

using namespace std;

/*
 * straight-forward toposort.
 *
 * the idea behind solving toposort with a bfs is:
 * 1. store the number of incoming edges of each node.
 * 2. push all nodes with 0 incoming edges in the bfs queue.
 * 3. start popping from the queue. each node you pop, add it to the order.
 * 4. when visiting the neighbours of a node, decrease the number of incoming
 * edges of that neighbour. if that number becomes 0, then push it in the queue.
 *
 * for this problem specifically:
 * don't forget to not print whitespace after the last node in the order.
*/

int main() {
  int n, m;
  while (cin >> n >> m, n != 0) {
    vector<vector<int>> g(n + 1);
    vector<int> in(n + 1, 0);

    for (int k = 0; k < m; ++k) {
      int i, j;
      cin >> i >> j;
      g[i].push_back(j);
      ++in[j];
    }

    queue<int> q;
    for (int v = 1; v <= n; ++v)
      if (in[v] == 0)
        q.push(v);

    bool first = true;
    while (q.size()) {
      int v = q.front();
      q.pop();
      if (not first)
        cout << " ";
      cout << v;
      first = false;
      for (auto u : g[v])
        if (--in[u] == 0)
          q.push(u);
    }
    cout << endl;
  }
}
