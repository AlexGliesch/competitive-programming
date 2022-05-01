#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  int x;
  while (cin >> x) {
    x *= 10000000;
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; ++i)
      cin >> v[i];
    sort(v.begin(), v.end());
    int yes = -1;
    for (int i = n - 1; i >= 0; --i) {
      if (binary_search(v.begin(), v.begin() + i, x - v[i])) {
        yes = x - v[i];
        break;
      }
    }
    if (yes != -1)
      cout << "yes " << yes << ' ' << x - yes << endl;
    else
      cout << "danger" << endl;
  }
}