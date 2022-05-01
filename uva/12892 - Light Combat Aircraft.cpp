#include <iostream>
#include <vector>

using namespace std;

/* Given a node k with n branches, each branch having size Si, 1 <= i <= n.
 * (the size of a branch Si is the number of nodes contained in that branch)
 *
 * The number of pairs that have k as LCA is:
 *
 * Sk + sum(i=1 to n-1) { sum(j =i+1 to n) { Si * Sj }}
 *
 * In other words: take the number of children in each branch and multiply
 * by the number of children in every other branch, and add all that together.
 * */

vector<vector<int>> g;
vector<int> n_children;

int get_num_children(int i) {
  if (g[i].size() == 0)
    return 0;
  if (n_children[i] == -1) {
    n_children[i] = g[i].size();
    for (auto j : g[i])
      n_children[i] += get_num_children(j);
  }
  return n_children[i];
}

int main() {
  ios_base::sync_with_stdio(false);
  int T;
  cin >> T;
  for (int t = 1; t <= T; ++t) {
    int N;
    cin >> N;
    g.clear();
    g.resize(N);
    n_children.clear();
    n_children.resize(N, -1);

    for (int i = 0; i < N; ++i) {
      int x;
      cin >> x;
      if (x)
        g[x - 1].push_back(i);
    }

    cout << "Forest#" << t << ":";

    for (int i = 0; i < N; ++i) {
      int n = g[i].size();
      int res = get_num_children(i);

      if (n != 0) {
        vector<int> S(n), S_acc(n);
        for (int j = 0; j < n; ++j)
          S[j] = 1 + get_num_children(g[i][j]);

        S_acc[n - 1] = S[n - 1];
        for (int j = n - 2; j >= 0; --j)
          S_acc[j] = S[j] + S_acc[j + 1];

        for (int i = 0; i < n - 1; ++i)
          res += S[i] * S_acc[i + 1];
      }
      cout << ' ' << res;
    }
    cout << endl;
  }
}