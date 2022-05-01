#include <iostream>
#include <queue>
#include <vector>

using namespace std;

typedef vector<int> vi;
typedef vector<bool> vb;

int r, c, b, s;
vector<vb> graph;
vector<vb> graph_n;
vector<vb> graph_s;
vector<int> north;
vector<int> south;
vector<vi> memo;

void find_north_margin(int x, int y) {
  if (graph[x][y] && !graph_n[x][y]) {
    graph_n[x][y] = true;
    north[y] = max(north[y], x);
    if (x > 0)
      find_north_margin(x - 1, y);
    if (x < r - 1)
      find_north_margin(x + 1, y);
    if (y > 0)
      find_north_margin(x, y - 1);
    if (y < c - 1)
      find_north_margin(x, y + 1);
  }
}

void find_south_margin(int x, int y) {
  if (graph[x][y] && !graph_s[x][y]) {
    graph_s[x][y] = true;
    south[y] = min(south[y], x);
    if (x > 0)
      find_south_margin(x - 1, y);
    if (x < r - 1)
      find_south_margin(x + 1, y);
    if (y > 0)
      find_south_margin(x, y - 1);
    if (y < c - 1)
      find_south_margin(x, y + 1);
  }
}

int dp(int i, int n) {
  if (n == b) {
    return 0;
  } else if (i >= c) {
    return 1000000;
  } else if (memo[i][n] > -1) {
    return memo[i][n];
  } else {
    return memo[i][n] = min(south[i] - north[i] - 1 + dp(i + s + 1, n + 1),
                            dp(i + 1, n));
  }
}

int main() {
  while (cin >> r >> c >> b >> s) {
    graph.assign(r, vector<bool>(c, 0));
    graph_n.assign(r, vector<bool>(c, false));
    graph_s.assign(r, vector<bool>(c, false));

    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++) {
        char a;
        cin >> a;
        graph[i][j] = (a == '#');
      }
    }

    north.assign(c, 0);
    find_north_margin(0, 0);

    south.assign(c, r - 1);
    find_south_margin(r - 1, c - 1);

    memo.assign(c, vector<int>(b, -1));
    cout << dp(0, 0) << endl;
  }
  return 0;
}