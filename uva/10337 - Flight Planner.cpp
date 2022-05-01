#include <algorithm>
#include <ciso646>
#include <iostream>
#include <vector>

using namespace std;

/* DP, quite simple. */

int main() {
  int N;
  cin >> N;
  for (int t = 0; t < N; ++t) {
    int X;
    cin >> X;
    X /= 100;

    vector<vector<int>> w(X, vector<int>(10));

    for (int j = 9; j >= 0; --j) {
      for (int i = 0; i < X; ++i) {
        cin >> w[i][j];
        w[i][j] = -w[i][j];
      }
    }

    vector<vector<int>> c(X, vector<int>(10, 9999999));
    c[0][0] = w[0][0];
    for (int i = 1; i < X; ++i) {
      for (int j = 0; j <= 9; ++j) {
        if (j == 9) {
          c[i][j] = w[i][j] + min(c[i - 1][j] + 30, c[i - 1][j - 1] + 60);
        } else if (j == 0) {
          c[i][j] = w[i][j] + min(c[i - 1][j] + 30, c[i - 1][j + 1] + 20);
        } else {
          c[i][j] = w[i][j] + min(min(c[i - 1][j] + 30, c[i - 1][j + 1] + 20),
                                  c[i - 1][j - 1] + 60);
        }
      }
    }

    cout << min(c[X - 1][0] + 30, c[X - 1][1] + 20) << endl << endl;
  }
}