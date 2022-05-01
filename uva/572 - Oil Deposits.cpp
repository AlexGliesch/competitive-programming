#include <ciso646>
#include <iostream>

using namespace std;

/* Count the number of connected components using flood fill. */

int R, C;
char grid[110][110];
int dr[] = {1, 1, 0, -1, -1, -1, 0, 1};
int dc[] = {0, 1, 1, 1, 0, -1, -1, -1};

void flood(int r, int c) {
  if (r < 0 or r >= R or c < 0 or c >= C or grid[r][c] == '*')
    return;
  grid[r][c] = '*';
  for (int i = 0; i < 8; ++i)
    flood(r + dr[i], c + dc[i]);
}

int main() {
  while (cin >> R >> C, R != 0) {
    for (int r = 0; r < R; ++r)
      for (int c = 0; c < C; ++c)
        cin >> grid[r][c];

    int num_deposits = 0;
    int r = 0, c = 0;
    while (r != R and c != C) {
      if (grid[r][c] == '@') {
        ++num_deposits;
        flood(r, c);
      }
      if (++c == C)
        c = 0, ++r;
    }

    cout << num_deposits << endl;
  }
}