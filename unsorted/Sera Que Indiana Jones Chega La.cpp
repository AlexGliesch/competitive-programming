#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <queue>
#include <vector>
#define mp make_pair
#define EPS 1e-8

using namespace std;

struct Point {
  Point(double x = 0, double y = 0) : x(x), y(y) {}
  double x, y;
};

double dist(const Point &a, const Point &b) {
  return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double dist_to_line(const Point &p, const Point &A, const Point &B,
                    Point *ret = NULL) {
  double scale = double((p.x - A.x) * (B.x - A.x) + (p.y - A.y) * (B.y - A.y)) /
                 ((B.x - A.x) * (B.x - A.x) + (B.y - A.y) * (B.y - A.y));
  Point r(A.x + scale * (B.x - A.x), A.y + scale * (B.y - A.y));
  if (ret)
    *ret = r;
  return dist(p, r);
}

double dist_to_line_segment(const Point &p, const Point &A, const Point &B,
                            Point *ret = NULL) {
  if ((B.x - A.x) * (p.x - A.x) + (B.y - A.y) * (p.y - A.y) < EPS) {
    if (ret)
      *ret = A;
    return dist(p, A);
  } else if ((A.x - B.x) * (p.x - B.x) + (A.y - B.y) * (p.y - B.y) < EPS) {
    if (ret)
      *ret = B;
    return dist(p, B);
  } else {
    return dist_to_line(p, A, B, ret);
  }
}

bool in_range(const Point &p, const Point &q, const Point &r) {
  return r.x <= max(p.x, q.x) and r.x >= min(p.x, q.x) and
         r.y <= max(p.y, q.y) and r.y >= min(p.y, q.y);
}

bool line_segments_intersect(const Point &p1, const Point &q1, const Point &p2,
                             const Point &q2, Point *ret = NULL) {
  double a1 = q1.y - p1.y, b1 = p1.x - q1.x, c1 = a1 * p1.x + b1 * p1.y;
  double a2 = q2.y - p2.y, b2 = p2.x - q2.x, c2 = a2 * p2.x + b2 * p2.y;
  double det = a1 * b2 - a2 * b1;
  if (abs(det) < EPS) { /* Lines are parallel */
    return in_range(p1, q1, p2) or in_range(p1, q1, q2) or
           in_range(p2, q2, p1) or in_range(p2, q2, q1);
  }
  Point r((b2 * c1 - b1 * c2) / det, (a1 * c2 - a2 * c1) / det);
  bool ans = in_range(p1, q1, r) and in_range(p2, q2, r);
  if (ans and ret)
    *ret = r;
  return ans;
}

double dist_line_seg_line_seg(const Point &A, const Point &B, const Point &C,
                              const Point &D) {
  if (line_segments_intersect(A, B, C, D))
    return 0;
  double dACD = dist_to_line_segment(A, C, D);
  double dBCD = dist_to_line_segment(B, C, D);
  double dCAB = dist_to_line_segment(C, A, B);
  double dDAB = dist_to_line_segment(D, A, B);
  return min(min(dACD, dBCD), min(dCAB, dDAB));
}

int main() {
  int N;
  while (cin >> N, N) {
    vector<vector<double>> m(N, vector<double>(N, 0));
    vector<pair<Point, Point>> walls;
    for (int i = 0; i < N; ++i) {
      Point a, b;
      int l;
      cin >> a.x >> a.y >> l;
      if (l >= 0) {
        b.x = a.x + l, b.y = a.y;
      } else {
        b.x = a.x, b.y = a.y + abs(l);
      }
      walls.push_back(mp(a, b));
    }
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        if (i == j)
          m[i][j] = 0;
        else {
          m[i][j] = dist_line_seg_line_seg(walls[i].first, walls[i].second,
                                           walls[j].first, walls[j].second);
        }
      }
    }

    priority_queue<pair<double, int>> pq;
    vector<double> dist(N, -1);
    dist[0] = 0;
    pq.push(mp(0, 0));

    while (pq.size()) {
      double d = -pq.top().first;
      int v = pq.top().second;
      pq.pop();

      if (abs(dist[v] - d) > EPS)
        continue;
      if (v == 1) {
        if (abs(d) < EPS)
          cout << "0.00" << endl;
        else
          cout << setprecision(2) << fixed << d << endl;
        break;
      }

      for (int i = 0; i < N; ++i) {
        if (v == i)
          continue;
        double cd = max(d, m[v][i]);
        if (dist[i] == -1 or dist[i] > cd) {
          dist[i] = cd;
          pq.push(mp(-cd, i));
        }
      }
    }
  }
}