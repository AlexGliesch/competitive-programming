#include <ciso646>
#include <iostream>
#include <vector>

/* Easy problem, brute force works */

using namespace std;

int N, n;

vector<vector<char>> vector_90_degrees(const vector<vector<char>> &v) {
  vector<vector<char>> w(n, vector<char>(n));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j)
      w[i][j] = v[n - j - 1][i];
  }
  return move(w);
}

int main() {
  while (cin >> N >> n, N and n) {
    vector<vector<char>> V(N, vector<char>(N)), v(n, vector<char>(n));
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j)
        cin >> V[i][j];
    }
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j)
        cin >> v[i][j];
    }

    for (int q = 0; q < 4; ++q) {
      int num_appearances = 0;
      for (int i = 0; i < N - n + 1; ++i) {
        for (int j = 0; j < N - n + 1; ++j) {
          bool dif = false;
          for (int k = 0; k < n; ++k) {
            for (int l = 0; l < n; ++l) {
              if (V[i + k][j + l] != v[k][l]) {
                dif = true;
                goto a;
              }
            }
          }
        a:
          if (not dif)
            ++num_appearances;
        }
      }
      cout << num_appearances;
      if (q != 3)
        cout << " ";
      v = vector_90_degrees(v);
    }
    cout << endl;
  }
}