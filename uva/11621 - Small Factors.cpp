#include <ciso646>
#include <climits>
#include <iostream>

using namespace std;

long long p2[50], p3[50];

int main() {
  ios_base::sync_with_stdio(false);
  long long m;
  p2[0] = p3[0] = 1;
  for (int i = 1; i < 50; ++i) {
    p2[i] = p2[i - 1] * 2;
    p3[i] = p3[i - 1] * 3;
  }
  while (cin >> m, m) {
    long long best = INT_MAX;
    int i, j;
    for (i = 0; p2[i] < m; ++i) {
      long long t = 0;
      for (j = 0; t < m; ++j)
        t = p2[i] * p3[j];
      if (t >= m and t < best)
        best = t;
    }
    if (p2[i] >= m and p2[i] < best)
      best = p2[i];
    cout << best << endl;
  }
}