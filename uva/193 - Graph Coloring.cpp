#include <ciso646>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

/* Try to make each vertex black, separately, using backtracking. Do that only
 * that vertex as no black neighbours (wait, that sounded racist...). */

vector<vector<int>> g;
int N, M;
set<int> black, best;

void backtrack(int v) {
  if (v == N) {
    if (best.size() < black.size())
      best = black;
    return;
  }

  bool can = true;
  for (int i = 0; i < g[v].size(); ++i)
    if (black.count(g[v][i])) {
      can = false;
      break;
    }

  if (can) {
    black.insert(v);
    backtrack(v + 1);
    black.erase(v);
  }
  backtrack(v + 1);
}

int main() {
  int T;
  cin >> T;
  for (int t = 0; t < T; ++t) {
    cin >> N >> M;
    g.clear();
    g.resize(N);
    for (int i = 0; i < M; ++i) {
      int x, y;
      cin >> x >> y;
      --x, --y;
      g[x].push_back(y);
      g[y].push_back(x);
    }

    black.clear();
    best.clear();
    backtrack(0);

    cout << best.size() << endl;
    for (set<int>::iterator i = best.begin(); i != best.end(); ++i) {
      if (i != best.begin())
        cout << " ";
      cout << *i + 1;
    }
    cout << endl;
  }
}