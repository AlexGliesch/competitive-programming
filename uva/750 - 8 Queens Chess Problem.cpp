#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>

using namespace std;

int qr, qc, sol;
int col[8];

void backtrack(int i, int cols_used) {
  if (i == 8) {
    cout << setw(2) << sol++ << "      ";
    for (int j = 0; j < 7; ++j)
      cout << col[j] + 1 << " ";
    cout << col[7] + 1 << endl;
    return;
  }

  if (i == qr) {
    backtrack(i + 1, cols_used);
    return;
  }

  for (int j = 0; j < 8; ++j) {
    if (cols_used & (1 << j))
      continue;
    if (abs(i - qr) == abs(j - qc))
      continue;
    for (int k = 0; k < i; ++k) {
      if (abs(i - k) == abs(j - col[k]))
        goto a;
    }
    col[i] = j;
    backtrack(i + 1, cols_used | (1 << j));
  a:;
  }
}

int main() {
  int T;
  cin >> T;
  for (int t = 0; t < T; ++t) {
    cin >> qc >> qr;
    --qr, --qc;

    sol = 1;
    if (t != 0)
      cout << endl;
    cout << "SOLN       COLUMN" << endl
         << " #      1 2 3 4 5 6 7 8" << endl
         << endl;

    col[qr] = qc;
    backtrack(0, (1 << qc));
  }
}