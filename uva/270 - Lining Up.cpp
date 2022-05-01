#include <algorithm>
#include <ciso646>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

using namespace std;

/* for each point, find the dx/dy ratio of every other point with respect to
 * the current one. count the number of occurences of each distinct ratio.
 *
 * you have to store the ratios in a map. however, you can't use float or
 * double, because of precision erros: you must minimize the fraction first.
 *
 * to minimize a fraction x/y, just do x/gcd(x,y) / y/gcd(x,y).
 * g++ has a hidden std::__gcd() in the stl!
 * */

int main() {
  ios_base::sync_with_stdio(false);
  int T;
  cin >> T;
  string s;
  getline(cin, s);
  getline(cin, s);
  for (int t = 0; t < T; ++t) {
    if (t)
      cout << endl;

    pair<int, int> points[700];
    int N = 0;

    while (getline(cin, s) and s.size()) {
      istringstream ss(s);
      ss >> points[N].first >> points[N].second;
      ++N;
    }

    int ans = 0;
    for (int i = 0; i < N; ++i) {
      map<pair<int, int>, int> dx_dy_frequencies;
      for (int j = 0; j < N; ++j) {
        if (i == j)
          continue;
        int dx = points[i].first - points[j].first;
        int dy = points[i].second - points[j].second;
        int gcd = __gcd(dx, dy);
        ++dx_dy_frequencies[make_pair(dx / gcd, dy / gcd)];
      }
      for (const auto &p : dx_dy_frequencies)
        ans = max(ans, 1 + p.second);
    }
    cout << ans << endl;
  }
}