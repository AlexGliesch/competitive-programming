#include <ciso646>
#include <iostream>

using namespace std;

/* just write some if's */

int main() {
  ios_base::sync_with_stdio(false);
  int K;
  while (cin >> K, K) {
    int n, m;
    cin >> n >> m;
    for (int k = 0; k < K; ++k) {
      int x, y;
      cin >> x >> y;
      if (x == n or y == m)
        cout << "divisa" << endl;
      else if (x > n and y > m)
        cout << "NE" << endl;
      else if (x > n and y < m)
        cout << "SE" << endl;
      else if (x < n and y > m)
        cout << "NO" << endl;
      else /*if (x < n and y < m)*/
        cout << "SO" << endl;
    }
  }
}