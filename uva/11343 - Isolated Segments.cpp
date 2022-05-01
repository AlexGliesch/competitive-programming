#include <algorithm>
#include <ciso646>
#include <cmath>
#include <iostream>
#include <vector>
#define eps 1e-9

using namespace std;

/* Basta verificar quais segmentos não interceptam nenhum outro. Cuidado com
 * segmentos paralelas, e segmentos contidos dentro de outros. */

struct Point {
  double x, y;
};

bool in_range(const Point &p, const Point &q, const Point &r) {
  return r.x <= max(p.x, q.x) and r.x >= min(p.x, q.x) and
         r.y <= max(p.y, q.y) and r.y >= min(p.y, q.y);
}

bool line_segments_intersect(const Point &p1, const Point &q1, const Point &p2,
                             const Point &q2) {
  double a1 = q1.y - p1.y, b1 = p1.x - q1.x, c1 = a1 * p1.x + b1 * p1.y;
  double a2 = q2.y - p2.y, b2 = p2.x - q2.x, c2 = a2 * p2.x + b2 * p2.y;
  double det = a1 * b2 - a2 * b1;
  if (abs(det) < eps) { /* Lines are parallel */
    return in_range(p1, q1, p2) or in_range(p1, q1, q2) or
           in_range(p2, q2, p1) or in_range(p2, q2, q1);
  }
  Point r = {(b2 * c1 - b1 * c2) / det, (a1 * c2 - a2 * c1) / det};
  return in_range(p1, q1, r) and in_range(p2, q2, r);
}

int main() {
  int T;
  cin >> T;
  for (int t = 0; t < T; ++t) {
    int N;
    cin >> N;
    vector<Point> p(N), q(N);
    for (int i = 0; i < N; ++i)
      cin >> p[i].x >> p[i].y >> q[i].x >> q[i].y;

    int ans = 0;
    for (int i = 0; i < N; ++i) {
      bool collide = false;
      for (int j = 0; j < N; ++j) {
        if (j == i)
          continue;
        collide = line_segments_intersect(p[i], q[i], p[j], q[j]);
        if (collide)
          break;
      }
      if (not collide)
        ++ans;
    }
    cout << ans << endl;
  }
}