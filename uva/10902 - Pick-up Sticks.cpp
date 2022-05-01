#include <algorithm>
#include <ciso646>
#include <cmath>
#include <iostream>
#include <vector>
#define eps 1e-9

using namespace std;

/* Basta verificar a intersecção com os segmentos: aqueles que não intersectam
* com nenhum jogado depois dele são top. Algoritmo da intersecção peguei do
* TopCoder, bem bom. */

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
  int n;
  vector<Point> p, q;
  while (cin >> n, n != 0) {
    p.resize(n), q.resize(n);
    for (int i = 0; i < n; ++i)
      cin >> p[i].x >> p[i].y >> q[i].x >> q[i].y;

    vector<int> top;
    for (int i = 0; i < n; ++i) {
      bool use = true;
      for (int j = i + 1; j < n; ++j)
        if (line_segments_intersect(p[j], q[j], p[i], q[i])) {
          use = false;
          break;
        }
      if (use)
        top.push_back(i);
    }

    cout << "Top sticks:";
    for (int i = 0; i < top.size(); ++i) {
      cout << ' ' << top[i] + 1 << (i == top.size() - 1 ? '.' : ',');
    }
    cout << endl;
  }
}