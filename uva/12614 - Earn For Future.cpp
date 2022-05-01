#include <algorithm>
#include <iostream>

using namespace std;

int main() {
  int T, n, x, val;
  cin >> T;
  for (int t = 0; t < T; ++t) {
    cin >> n;
    val = 0;
    for (int i = 0; i < n; ++i) {
      cin >> x;
      val = max(val, x);
    }
    cout << "Case " << t + 1 << ": " << val << endl;
  }
}