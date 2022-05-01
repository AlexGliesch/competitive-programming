#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

vector<vector<int>> all_solutions;
vector<int> row(8), solution(8);

void find_all_solutions(int c, int rows_used) {
  if (c == 8) {
    all_solutions.push_back(row);
    return;
  }
  for (int r = 0; r < 8; ++r) {
    if (rows_used & (1 << r))
      continue;
    for (int k = 0; k < c; ++k) {
      if (abs(c - k) == abs(r - row[k]))
        goto leave;
    }
    row[c] = r;
    find_all_solutions(c + 1, rows_used | (1 << r));
  leave:;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  find_all_solutions(0, 0);
  int T = 1;
  string buf;
  while (getline(cin, buf)) {
    istringstream ss(buf);
    for (int i = 0; i < 8; ++i)
      ss >> solution[i];
    int min_dist = 9;
    for (const auto &s : all_solutions) {
      int sol_dist = 0;
      for (int i = 0; i < 8; ++i)
        if (s[i] != solution[i] - 1)
          ++sol_dist;
      min_dist = min(min_dist, sol_dist);
    }
    cout << "Case " << T++ << ": " << min_dist << endl;
  }
}