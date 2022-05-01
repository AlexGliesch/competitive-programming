#include <ciso646>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/* Very simple because brute force works. */

vector<int> h, l;
vector<string> names;

int main() {
  ios_base::sync_with_stdio(false);
  int T;
  cin >> T;
  for (int t = 0; t < T; ++t) {
    if (t)
      cout << '\n';
    int D;
    cin >> D;
    h.resize(D), l.resize(D), names.resize(D);
    for (int i = 0; i < D; ++i)
      cin >> names[i] >> l[i] >> h[i];
    int Q;
    cin >> Q;
    for (int q = 0; q < Q; ++q) {
      int P;
      cin >> P;
      int found = -1;
      for (int i = 0; i < D; ++i) {
        if (P >= l[i] and P <= h[i]) {
          if (found != -1) {
            found = -1;
            goto leave;
          }
          found = i;
        }
      }
    leave:
      if (found == -1)
        cout << "UNDETERMINED" << endl;
      else
        cout << names[found] << endl;
    }
  }
}