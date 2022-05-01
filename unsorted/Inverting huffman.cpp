#include <iostream>
#include <vector>

using namespace std;

typedef vector<long long> vll;

int main() {
  long long n;
  while (cin >> n) {
    vll v(51, 0);
    for (int i = 0; i < n; i++) {
      long long l;
      cin >> l;
      v[l]++;
    }

    long long p = 1;
    vector<vll> mat(51, vll());
    for (int i = 50; i >= 0; i--) {
      long long ps = (i == 50) ? 0 : mat[i + 1].size() / 2;
      // cout << "Level " << i << " has " << (ps + v[i]) << " elements."
      // << endl;
      if (ps + v[i] > 0) {
        // cout << "ola" << endl;
        mat[i].assign(v[i] + ps, p);
        for (int j = 0; j < ps; j++) {
          mat[i][j] = mat[i + 1][j * 2] + mat[i + 1][j * 2 + 1];
          p = max(p, mat[i][j]);
        }
      }
    }

    cout << mat[0][0] << endl;
  }

  return 0;
}