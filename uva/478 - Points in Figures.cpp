#include <ciso646>
#include <cmath>
#include <iostream>
#include <vector>
#define eps 1e-9
#define pi 3.14159265358979323846

using namespace std;

struct Point {
  Point(double x = 0, double y = 0) : x(x), y(y) {}
  double x, y;
};

double dist_sq(const Point &p1, const Point &p2) {
  return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

/*  > 0 ccw
*  < 0 cw
*  = 0 collinear*/
double cross(const Point &p, const Point &q, const Point &r) {
  return (q.x - p.x) * (r.y - p.y) - (q.y - p.y) * (r.x - p.x);
}

double angle(const Point &p, const Point &q, const Point &r) {
  double ux = q.x - p.x, uy = q.y - p.y;
  double vx = r.x - p.x, vy = r.y - p.y;
  return acos((ux * vx + uy * vy) /
              sqrt((ux * ux + uy * uy) * (vx * vx + vy * vy)));
}

struct Figure {
  virtual bool contains(const Point &p) const = 0;
};

struct Polygon : public vector<Point>, public Figure {
  bool contains(const Point &p) const override {
    const vector<Point> &P = (vector<Point> &)*this;
    if ((int)P.size() == 0)
      return false;
    double sum = 0;
    /* This implementation assumes first vertex is equal to last one */
    for (int i = 0; i < (int)P.size() - 1; ++i) {
      if (cross(p, P[i], P[i + 1]) < 0) {
        sum -= angle(p, P[i], P[i + 1]);
      } else {
        sum += angle(p, P[i], P[i + 1]);
      }
    }
    return (abs(sum - 2 * pi) < eps or abs(sum + 2 * pi) < eps);
  }
};

struct Circle : public Figure {
  bool contains(const Point &p) const override {
    return dist_sq(center, p) <= radius * radius;
  }
  double radius;
  Point center;
};

int main() {
  char c;
  vector<Figure *> figures;
  while (cin >> c, c != '*') {
    if (c == 'r') {
      Point ul, lr;
      cin >> ul.x >> ul.y >> lr.x >> lr.y;
      auto polygon = new Polygon;
      polygon->push_back(ul);
      polygon->emplace_back(lr.x, ul.y);
      polygon->push_back(lr);
      polygon->emplace_back(ul.x, lr.y);
      polygon->push_back(ul);
      figures.push_back(polygon);
    } else if (c == 't') {
      Point a, b, c;
      cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y;
      auto polygon = new Polygon;
      polygon->push_back(a);
      polygon->push_back(b);
      polygon->push_back(c);
      polygon->push_back(a);
      figures.push_back(polygon);
    } else if (c == 'c') {
      auto circle = new Circle;
      cin >> circle->center.x >> circle->center.y >> circle->radius;
      figures.push_back(circle);
    }
  }

  Point p;
  int counter = 1;
  while (cin >> p.x >> p.y, p.x != 9999.9 or p.y != 9999.9) {
    bool is_contained = false;
    for (int i = 0; i < figures.size(); ++i) {
      if (figures[i]->contains(p)) {
        is_contained = true;
        cout << "Point " << counter << " is contained in figure " << i + 1
             << endl;
      }
    }
    if (not is_contained) {
      cout << "Point " << counter << " is not contained in any figure" << endl;
    }
    ++counter;
  }
}