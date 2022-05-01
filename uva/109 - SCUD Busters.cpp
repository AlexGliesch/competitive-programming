#include <algorithm>
#include <ciso646>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>
#define eps 1e-9
#define pi 3.14159265358979323846

/* Problema interessante, bem completo.
 * Primeiro encontrar a CH, depois testar se um ponto está dentro de um
 * polígono, e depois ver área do polígono.
 *
 * Nota: não esquecer de colocar endl no fim, muito embora o output seja só
 * um número!*/

using namespace std;

struct Point {
  int x, y;
  bool operator<(const Point &p) const {
    return x < p.x or (x == p.x and y < p.y);
  }
};

/*  > 0 ccw
*  < 0 cw
*  = 0 collinear*/
int cross(const Point &p, const Point &q, const Point &r) {
  return (q.x - p.x) * (r.y - p.y) - (q.y - p.y) * (r.x - p.x);
}

double angle(const Point &p, const Point &q, const Point &r) {
  int ux = q.x - p.x, uy = q.y - p.y;
  int vx = r.x - p.x, vy = r.y - p.y;
  return acos((ux * vx + uy * vy) /
              sqrt((ux * ux + uy * uy) * (vx * vx + vy * vy)));
}

vector<Point> convex_hull(vector<Point> P) {
  int n = P.size(), k = 0;
  vector<Point> H(2 * n);

  sort(P.begin(), P.end());

  for (int i = 0; i < n; i++) {
    while (k >= 2 and cross(H[k - 2], H[k - 1], P[i]) < 0)
      k--;
    H[k++] = P[i];
  }

  for (int i = n - 2, t = k + 1; i >= 0; i--) {
    while (k >= t and cross(H[k - 2], H[k - 1], P[i]) < 0)
      k--;
    H[k++] = P[i];
  }

  H.resize(k);
  return H;
}

bool point_in_polygon(const Point &p, const vector<Point> &P) {
  /* Assumes first vertex is equal to last vertex */
  if ((int)P.size() == 0)
    return false;
  double sum = 0;
  for (int i = 0; i < (int)P.size() - 1; ++i) {
    if (cross(p, P[i], P[i + 1]) < 0) {
      sum -= angle(p, P[i], P[i + 1]);
    } else {
      sum += angle(p, P[i], P[i + 1]);
    }
  }
  return (abs(sum - 2 * pi) < eps or abs(sum + 2 * pi) < eps);
}

double area_of_polygon(const vector<Point> &P) {
  /* Assumes first vertex is equal to last vertex */
  double sum = 0.0;
  for (int i = 0; i < (int)P.size() - 1; ++i) {
    sum += (P[i].x * P[i + 1].y - P[i + 1].x * P[i].y);
  }
  return abs(sum) / 2.0;
}

int main() {
  vector<vector<Point>> kingdoms;
  int k;
  while (cin >> k, k != -1) {
    vector<Point> kingdom(k);
    for (int i = 0; i < k; ++i)
      cin >> kingdom[i].x >> kingdom[i].y;
    kingdoms.emplace_back(convex_hull(kingdom));
  }

  Point p;
  double area_sum = 0.0;
  vector<bool> out(kingdoms.size(), false);

  while (cin >> p.x >> p.y) {
    for (int i = 0; i < kingdoms.size(); ++i) {
      if (not out[i] and point_in_polygon(p, kingdoms[i])) {
        out[i] = true;
        area_sum += area_of_polygon(kingdoms[i]);
      }
    }
  }

  cout << setprecision(2) << fixed << area_sum << endl;
}