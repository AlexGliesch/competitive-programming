#include <ciso646>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <vector>
#define eps 1e-9

using namespace std;

/* Dados vários segmentos de reta e um ponto M, encontrar o segmento que
 * tem a menor distância de M, e printar as coordenadas da intersecção. */

struct Point {
  double x, y;
};

double dist(const Point &a, const Point &b) {
  return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double dist_to_line(const Point &p, const Point &A, const Point &B, Point &c) {
  double scale = double((p.x - A.x) * (B.x - A.x) + (p.y - A.y) * (B.y - A.y)) /
                 ((B.x - A.x) * (B.x - A.x) + (B.y - A.y) * (B.y - A.y));
  c.x = A.x + scale * (B.x - A.x);
  c.y = A.y + scale * (B.y - A.y);
  return dist(p, c);
}

double dist_to_line_segment(const Point &p, const Point &A, const Point &B,
                            Point &c) {
  if ((B.x - A.x) * (p.x - A.x) + (B.y - A.y) * (p.y - A.y) < eps) {
    c = A;
    return dist(p, A);
  } else if ((A.x - B.x) * (p.x - B.x) + (A.y - B.y) * (p.y - B.y) < eps) {
    c = B;
    return dist(p, B);
  } else
    return dist_to_line(p, A, B, c);
}

Point M;
int N;
vector<Point> P;

int main() {
  cout << setprecision(4) << fixed;
  while (cin >> M.x >> M.y >> N) {
    P.resize(N + 1);
    for (int i = 0; i < N + 1; ++i) {
      cin >> P[i].x >> P[i].y;
    }
    double min_dist = numeric_limits<double>::max();
    Point closest;
    for (int i = 0; i < N; ++i) {
      Point c;
      double d = dist_to_line_segment(M, P[i], P[i + 1], c);
      if (d < min_dist) {
        min_dist = d;
        closest = c;
      }
    }
    cout << closest.x << endl << closest.y << endl;
  }
}