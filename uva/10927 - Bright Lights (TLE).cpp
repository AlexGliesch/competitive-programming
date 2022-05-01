#include <algorithm>
#include <ciso646>
#include <cmath>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

/* TLE. Dica: dois pontos são colineares com a origem se o coeficiente angular
 * da reta que eles formam com (0, 0) é igual! Assim fica muito mais fácil. */

struct Point {
  int x, y, z;
  bool operator<(const Point &p) const {
    return x * p.y < y * p.x or x * p.y == y * p.x and z < p.z;
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  int T = 1, N;
  while (cin >> N, N) {
    vector<Point> P(N), invisible;
    for (auto &p : P)
      cin >> p.x >> p.y >> p.z;

    sort(begin(P), end(P));

    for (int k = 0; k < N; ++k) {
      int j = k + 1;
      while (P[k].x * P[j].y == P[k].y * P[j].x)
        ++j;
    }

    sort(begin(invisible), end(invisible), [](const Point &a, const Point &b) {
      return make_pair(a.x, a.y) < make_pair(b.x, b.y);
    });

    cout << "Data set " << T++ << ":" << endl;
    if (invisible.empty()) {
      cout << "All the lights are visible." << endl;
    } else {
      cout << "Some lights are not visible:" << endl;
      for (int i = 0; i < invisible.size(); ++i) {
        cout << "x = " << invisible[i].x << ", y = " << invisible[i].y
             << (i == invisible.size() - 1 ? '.' : ';') << endl;
      }
    }
  }
}