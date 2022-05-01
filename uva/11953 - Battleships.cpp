#include <algorithm>
#include <ciso646>
#include <iostream>
#include <vector>

using namespace std;

/* Flood fill. A boat is alive if it has at least one 'x'. */

vector<vector<char>> g;
int T, N;

int dr[] = {1, 1, 0, -1, -1, -1, 0, 1};
int dc[] = {0, 1, 1, 1, 0, -1, -1, -1};

int flood(int r, int c) {
  if (r < 0 or r >= N or c < 0 or c >= N or g[r][c] == '.')
    return 0;
  int alive = (g[r][c] == 'x' ? 1 : 0);
  g[r][c] = '.';
  for (int i = 0; i < 8; ++i) {
    alive = max(alive, flood(r + dr[i], c + dc[i]));
  }
  return alive;
}

int main() {
  cin >> T;
  for (int t = 1; t <= T; ++t) {
    cin >> N;
    g.clear();
    g.resize(N, vector<char>(N));

    for (int i = 0; i < N; ++i)
      for (int j = 0; j < N; ++j)
        cin >> g[i][j];

    int ships = 0;
    for (int i = 0; i < N; ++i)
      for (int j = 0; j < N; ++j)
        ships += flood(i, j);

    cout << "Case " << t << ": " << ships << endl;
  }
}