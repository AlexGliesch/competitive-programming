#include <algorithm>
#include <iostream>

using namespace std;

/* implesmente pegar a mediana dos x (Street) e dos y (Avenue). */

int main() {
  int T, R, C, F, x[50100], y[50100];
  cin >> T;
  while (T--) {
    cin >> R >> C >> F;
    for (int i = 0; i < F; ++i)
      cin >> x[i] >> y[i];

    sort(x, x + F);
    sort(y, y + F);

    cout << "(Street: " << x[(F - 1) / 2] << ", Avenue: " << y[(F - 1) / 2]
         << ")" << endl;
  }
}