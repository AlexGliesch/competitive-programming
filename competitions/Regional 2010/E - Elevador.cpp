#include <iostream>
#include <algorithm>
#include <cmath>
#include <ciso646>
#define mp make_pair
#define EPS 1e-10

using namespace std;

/* put the bigger circle on the top-left corner, and try the smaller circle on 
 * the three remaining corners. if any of the placements doesn't intersect 
 * with the big circle, return true, else false. 
 * the challenge in this problem is get a function that tells whether two 
 * circles intersect.
 * */

struct Point{
	Point(int x = 0, int y = 0) : x(x), y(y) { }
	
    double norm() const {
		return sqrt(x*x + y*y);
    }

	int x, y;
};

struct Circle {
	double r, x, y;

	Circle(double r = 0, double x = 0, double y = 0) : r(r), x(x), y(y) {}

	/* intersection of this circle and another circle c2. returns the number 
	 * of solutions (0, 1 or 2), and the intersected points in i1 and i2. */
	int circle_circle_intersection(const Circle& c2, Point& i1, Point& i2) const {
		double d = Point(x - c2.x, y - c2.y).norm();
		// find number of solutions
		if (d - (r + c2.r) > -EPS) {
			// circles are too far apart, no solution(s)
			return 0;
		} else if (std::abs(d) < EPS and std::abs(double(r - c2.r)) < EPS) {
			// circles coincide, infinite solutions
			return 2;
		} else if (d + min(r, c2.r) - max(r, c2.r) < EPS) {
			// one circle contains the other
			return 2;
		} else {
			double a = (r*r - c2.r*c2.r + d*d) / (2.0*d);
			double h = sqrt(r*r - a*a);

			Point p2(x + (a*(c2.x - x)) / d, 
				y + (a*(c2.y - y)) / d);
			i1.x = p2.x + h * (c2.y - y) / d;
			i1.y = p2.y - h * (c2.x - x) / d;

			i2.x = p2.x - h * (c2.y - y) / d;
			i2.y = p2.y + h * (c2.x - x) / d;
			if (abs(d - double(r + c2.r)) < EPS) {
				return 1;
			} else {
				return 2;
			}
		}
	}
};
  

int main() {
	ios_base::sync_with_stdio(false);
	int w, h, r1, r2;
	while (cin >> w >> h >> r1 >> r2, w or h or r1 or r2) {
		int bigr = max(r1, r2);
		int smallr = min(r1, r2);

		if (bigr * 2 > w or bigr * 2 > h) {
			cout <<"N\n";
			continue;
		}

		Circle bigcircle(bigr, bigr, bigr);
		Circle smallcircle1(smallr, smallr, h - smallr);
		Circle smallcircle2(smallr, w - smallr, smallr);
		Circle smallcircle3(smallr, w - smallr, h - smallr);

		Point p1, p2;
		bool ans = false;
		if (bigcircle.circle_circle_intersection(smallcircle1, p1, p2) != 2) ans = true;
		if (bigcircle.circle_circle_intersection(smallcircle2, p1, p2) != 2) ans = true;
		if (bigcircle.circle_circle_intersection(smallcircle3, p1, p2) != 2) ans = true;
		if (ans) cout << "S\n";
		else cout<<"N\n";
	}
	
}