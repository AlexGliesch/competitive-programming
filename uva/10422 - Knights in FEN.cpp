#include <algorithm>
#include <ciso646>
#include <cstring>
#include <iostream>
#include <string>

using namespace std;

/* Quite interesting problem: graph + backtracking.
 * Solved using dfs, testing, at each iteration, if it worked, using strcmp.
 * */

char g[5][6];
const char *model[] = {"11111", "01111", "00 11", "00001", "00000"};
int win_moves, start_r, start_c;

bool check_win() {
  if (g[2][2] != ' ')
    return false;
  for (int i = 0; i < 5; ++i) {
    if (strcmp(g[i], model[i]))
      return false;
  }
  return true;
}

void dfs(int r, int c, int last_r, int last_c, int num_moves);

void visit(int new_r, int new_c, int r, int c, int last_r, int last_c,
           int num_moves) {
  if (new_r < 0 or new_c < 0 or new_r > 4 or new_c > 4 or
      (new_c == last_c and new_r == last_r))
    return;
  swap(g[r][c], g[new_r][new_c]);
  dfs(new_r, new_c, r, c, 1 + num_moves);
  swap(g[r][c], g[new_r][new_c]);
}

void dfs(int r, int c, int last_r, int last_c, int num_moves) {
  if (num_moves > 10)
    return;
  if (check_win()) {
    win_moves = min(win_moves, num_moves);
  }
  visit(r + 2, c + 1, r, c, last_r, last_c, num_moves);
  visit(r + 2, c - 1, r, c, last_r, last_c, num_moves);
  visit(r - 2, c + 1, r, c, last_r, last_c, num_moves);
  visit(r - 2, c - 1, r, c, last_r, last_c, num_moves);
  visit(r + 1, c + 2, r, c, last_r, last_c, num_moves);
  visit(r + 1, c - 2, r, c, last_r, last_c, num_moves);
  visit(r - 1, c + 2, r, c, last_r, last_c, num_moves);
  visit(r - 1, c - 2, r, c, last_r, last_c, num_moves);
}

int main() {
  int t;
  cin >> t;
  string s;
  getline(cin, s);
  while (t--) {
    for (int i = 0; i < 5; ++i) {
      getline(cin, s);
      strcpy(g[i], s.c_str());
      g[i][5] = '\0';
      for (int j = 0; j < 5; ++j) {
        if (g[i][j] == ' ') {
          start_r = i;
          start_c = j;
        }
      }
    }
    win_moves = 11;
    dfs(start_r, start_c, -1, -1, 0);
    if (win_moves > 10)
      cout << "Unsolvable in less than 11 move(s)." << endl;
    else
      cout << "Solvable in " << win_moves << " move(s)." << endl;
  }
}