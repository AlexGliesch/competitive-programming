#include <vector>
#include <cmath>
#include <cstdio>
#define mp make_pair
#define EPS 1e-5

using namespace std;

struct Point {
	Point(double x = 0, double y = 0) : x(x), y(y) {}
	bool operator<(const Point& p) const { return y < p.y or (y == p.y and x < p.x); }
	bool operator==(const Point& p) const { return abs(x - p.x) < EPS and abs(y - p.y) < EPS; }
	double norm() const { return sqrt(x * x + y * y); }
	double x, y;
};

double dist(const Point& a, const Point& b) {
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

struct line {
	line(Point p1, Point p2) : p1(p1), p2(p2) {}
	Point p1, p2;
};

vector<line> lines;
vector<Point> vertices;
vector<vector<pair<double, int> > > g;

bool in_range(const Point& p, const Point& q, const Point& r) {
	return r.x <= max(p.x, q.x) and r.x >= min(p.x, q.x) and r.y <= max(p.y, q.y) and
		   r.y >= min(p.y, q.y);
}

bool line_segments_intersect(line l1, line l2, Point* ret = NULL) {
	const Point &p1 = l1.p1, &q1 = l1.p2, &p2 = l2.p1, &q2 = l2.p2;
	double a1 = q1.y - p1.y, b1 = p1.x - q1.x, c1 = a1 * p1.x + b1 * p1.y;
	double a2 = q2.y - p2.y, b2 = p2.x - q2.x, c2 = a2 * p2.x + b2 * p2.y;
	double det = a1 * b2 - a2 * b1;
	if (abs(det) < EPS) { /* Lines are parallel */
		return false;
		// return in_range(p1, q1, p2) or in_range(p1, q1, q2) or in_range(p2, q2, p1) or
		// 	   in_range(p2, q2, q1);
	}
	Point r((b2 * c1 - b1 * c2) / det, (a1 * c2 - a2 * c1) / det);
	bool ans = in_range(p1, q1, r) and in_range(p2, q2, r);
	if (ans and ret) *ret = r;
	return ans;
}

int main() {
	int t;
	scanf("%d", &t);
	for (int T = 1; T <= t; ++T) {
		printf("Case #%d:", T);
		int w, h, n;
		scanf("%d %d %d", &w, &h, &n);
		lines.clear();
		vertices.clear();
		for (int i = 0; i < n; ++i) {
			int xi, yi, wi, hi;
			scanf("%d %d %d %d", &xi, &yi, &wi, &hi);
			Point p1(xi, yi), p2(xi + wi, yi), p3(xi, yi + hi), p4(xi + wi, yi + hi);
			lines.push_back(line(p1, p2));
			lines.push_back(line(p1, p3));
			lines.push_back(line(p2, p4));
			lines.push_back(line(p3, p4));
			vertices.push_back(p1);
			vertices.push_back(p2);
			vertices.push_back(p3);
			vertices.push_back(p4);
		}
		Point first, last;
		scanf("%lf %lf", &first.x, &first.y);
		scanf("%lf %lf", &last.x, &last.y);
		vertices.push_back(first);
		vertices.push_back(last);

		g.clear();
		for (int i = 0; i < vertices.size(); ++i) {
			for (int j = i + 1; j < vertices.size(); ++j) {
				// test for pair vertices[i] and vertices[j] if there is an unobstructed line
				bool ok = true;
				for (int k = 0; k < lines.size(); ++k) {
					if (line_segments_intersect(line(vertices[i], vertices[j]), lines[k])) {
						ok = false;
						break;
					}
				}
				if (ok) {
					double d = dist(vertices[i], vertices[j]);
					g[i].push_back(mp(d, j));
					g[j].push_back(mp(d, i));
				}
			}
		}

        // dijkstra em g 
        
	}
}