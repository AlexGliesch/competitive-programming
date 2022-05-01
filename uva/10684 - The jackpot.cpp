#include <algorithm>
#include <iostream>

using namespace std;

int main() {
  int n, v[10001];
  while (cin >> n, n) {
    int res = -1, min_value = 0;
    for (int ub = 0; ub < n; ++ub) {
      cin >> v[ub];
      if (ub > 0)
        v[ub] += v[ub - 1];
      res = max(res, v[ub] - min_value);
      min_value = min(min_value, v[ub]);
    }
    if (res > 0)
      cout << "The maximum winning streak is " << res << ".\n";
    else
      cout << "Losing streak.\n";
  }
}