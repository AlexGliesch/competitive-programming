#include <algorithm>
#include <iostream>

using namespace std;

/* Flood fill, podendo dar a volta horizontalmente (nas colunas).
 *
 * Cuidado: não necessariamente as letras usadas são w e l; podem ser usadas
 * quaisquer duas letras. */

char g[20][20], land;
int R, C, X, Y, biggest;
int dr[] = {1, -1, 0, 0}, dc[] = {0, 0, 1, -1};

int flood(int r, int c) {
  if (g[r][c] != land)
    return 0;
  int res = 1;
  g[r][c] = '\0';
  for (int i = 0; i < 4; ++i) {
    int ri = r + dr[i], ci = (c + dc[i]) % C;
    if (ri < 0 || ri >= R)
      continue;
    res += flood(ri, ci < 0 ? C - 1 : ci);
  }
  return res;
}

int main() {
  while (cin >> R >> C) {
    for (int i = 0; i < R; ++i)
      for (int j = 0; j < C; ++j)
        cin >> g[i][j];
    cin >> X >> Y;

    land = g[X][Y];
    flood(X, Y);

    biggest = 0;
    for (int r = 0; r < R; ++r)
      for (int c = 0; c < C; ++c) {
        biggest = max(biggest, flood(r, c));
      }

    cout << biggest << endl;
  }
}