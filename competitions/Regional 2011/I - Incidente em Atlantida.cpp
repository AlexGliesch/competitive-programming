#include <cmath>
#include <algorithm>
#include <ciso646>
#include <vector>
#include <iomanip>
#include <iostream>
#include <queue>
#include <limits>
#include <functional>
#define EPS 1e-9
#define mp make_pair

using namespace std;

/* 
 * idea: construct a graph where the nodes are:
 * - the mural boundaries
 * - the teletransportation cabins
 * - the start and end points
 * 
 * and there is an edge between one node and another if there is a straight
 * line between their positions that does not intersect any of the murals. the
 * cost of the edge is the euclidean distance, or 0, if both endpoints are
 * teletransportation devices. 
 * 
 * run a dijkstra on that graph. the dijkstra state is (v, t), where v is the 
 * current vertex and t is how many teletransports you have left. when taking 
 * an edge with a teletransport (weight 0), decrement t, and if t is less than
 * 0, do not take it. the initial node (v, t) starts with (start_point, T).
 * 
 * i don't know if it's necessary, but: take care of line segments that
 * have their endpoints outside the circle with 10^5 radius. you might need
 * to constrain the line segment endpoints to be inside the island.
 * */

struct Point {
	Point(double x = 0, double y = 0) : x(x), y(y) {}
	bool operator==(const Point& p) const {
		return abs(x - p.x) < EPS and abs(y - p.y) < EPS;
	}
	double norm() const {
		return sqrt(x*x + y*y);
	}
	bool operator!=(const Point& p) const { return not(*this == p); }
	double x, y;
};

bool in_range(const Point& p, const Point& q, const Point& r) {
	return r.x <= max(p.x, q.x) and r.x >= min(p.x, q.x)
		and r.y <= max(p.y, q.y) and r.y >= min(p.y, q.y);
}

bool line_segments_intersect(const Point& p1, const Point& q1,
	const Point& p2, const Point& q2) {
	double a1 = q1.y - p1.y, b1 = p1.x - q1.x, c1 = a1 * p1.x + b1 * p1.y;
	double a2 = q2.y - p2.y, b2 = p2.x - q2.x, c2 = a2 * p2.x + b2 * p2.y;
	double det = a1 * b2 - a2 * b1;
	if (abs(det) < EPS) { /* Lines are parallel */
		return in_range(p1, q1, p2) or in_range(p1, q1, q2)
			or in_range(p2, q2, p1) or in_range(p2, q2, q1);
	}
	Point r((b2 * c1 - b1 * c2) / det, (a1 * c2 - a2 * c1) / det);
	return in_range(p1, q1, r) and in_range(p2, q2, r);
}

double dist2d(const Point& a, const Point& b) {
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

struct Circle {
	int r, x, y;

	Circle(int r = 0, int x = 0, int y = 0) : r(r), x(x), y(y) {}

	/* returns true if p is inside circle */
	bool inside(const Point& p) {
		return dist2d(p, Point(x, y)) < r;
	}

	int circle_line_intersection(const Point& p1, const Point& p2,
								 Point& out1, Point& out2) {
		if (inside(p1) and inside(p2)) return 0;
			
		Point lp1(p1.x - x, p1.y - y);
		Point lp2(p2.x - x, p2.y - y);

		/* not 100% sure if normalization is correct here! */
		Point p2minusp1(lp2.x - lp1.x, lp2.y - lp1.y);
		p2minusp1.x /= p2minusp1.norm();
		p2minusp1.y /= p2minusp1.norm();

		double a = pow(p2minusp1.x, 2) + pow(p2minusp1.y, 2);
		double b = 2 * ((p2minusp1.x * lp1.x) + (p2minusp1.y * lp1.y));
		double c = pow(lp1.x, 2) + pow(lp1.y, 2) - pow(r, 2);

		double delta = b * b - 4 * a * c;
		if (delta < 0) {
			/* No intersection */
			return 0; 
		} else if (delta == 0) {
			/* One intersection */
			double u = -b / (2.0 * a);
			out1 = Point(p1.x + (u * p2minusp1.x), p1.y + (u * p2minusp1.y));
			return 1;
		} else /*if (delta > 0)*/ {
			/* Two intersections */
			double sd = sqrt(delta);
			double u1 = (-b + sd) / (2.0 * a);
			double u2 = (-b - sd) / (2.0 * a);

			out1 = Point(p1.x + u1 * p2minusp1.x, p1.y + u1 * p2minusp1.y);
			out2 = Point(p1.x + u2 * p2minusp1.x, p1.y + u2 * p2minusp1.y);
			return 2;
		}
	}
};

/* a state is a pair (v, t), where v is the current node, and t
* is the number of teletransports left */
struct State {
	State(int v, int t, double g) : v(v), t(t), g(g) {
	}
	bool operator<(const State& s) const {
		return g > s.g;
	}
	double g;
	int v, t;
};

Circle main_circle = Circle(pow(10.0, 5), 0, 0);
int T, M, C;

int main() {
	ios_base::sync_with_stdio(false);
	while (cin >> T >> M >> C) {
		vector<pair<Point, Point> > murals(M);
		vector<Point> P;

		for (int i = 0; i < M; ++i) {
			cin >> murals[i].first.x >> murals[i].first.y
				>> murals[i].second.x >> murals[i].second.y;

			/* bound line segment extremities to circle boundary */
			Point o1, o2;
			int intersections = main_circle.circle_line_intersection(
				murals[i].first, murals[i].second, o1, o2);
			if (intersections == 1) {
				if (not main_circle.inside(murals[i].first)) {
					murals[i].first = o1;
				} else { // murals[i].second is outside
					murals[i].second = o1;
				}
			} else if (intersections == 2) {
				murals[i].first = o1;
				murals[i].second = o2;
			}
			P.push_back(murals[i].first);
			P.push_back(murals[i].second);
		}

		vector<Point> cabins(C);
		for (int i = 0; i < C; ++i) {
			cin >> cabins[i].x >> cabins[i].y;
			P.push_back(cabins[i]);
		}

		Point start, end;
		cin >> start.x >> start.y >> end.x >> end.y;
		P.push_back(start);
		P.push_back(end);
		int start_index = P.size() - 2, end_index = P.size() - 1;

		vector<vector<pair<int, double> > > g(P.size());

		for (int i = 0; i < P.size(); ++i) {
			const Point& pi = P[i];
			for (int j = i + 1; j < P.size(); ++j) {
				const Point& pj = P[j];
				bool has_obstacle = false;
				for (int m = 0; m < M; ++m) {
					const Point& m1 = murals[m].first, &m2 = murals[m].second;
					if (m1 != pi and m2 != pi and m1 != pj and m2 != pj and
						line_segments_intersect(m1, m2, pi, pj)) {
						has_obstacle = true;
						break;
					}
				}
				if (not has_obstacle) {
					double d;
					if (i >= 2 * M and i < 2 * M + C and 
						j >= 2 * M and j < 2 * M + C) {
						d = 0;
					} else {
						d = dist2d(pi, pj);
					}
					g[i].push_back(mp(j, d));
					g[j].push_back(mp(i, d));
				}
			}
		}

		double ans = -1;
		
		vector<vector<double> > dist(g.size(), vector<double>(T + 1,
			numeric_limits<double>::max()));
		priority_queue<State> pq;
		dist[start_index][T] = 0.0;
		pq.push(State(start_index, T, 0));

		while (pq.size()) {
			State s = pq.top();
			pq.pop();

			if (dist[s.v][s.t] != s.g) continue;
			if (s.v == end_index) {
				ans = s.g;
				break;
			}
			for (int i = 0; i < g[s.v].size(); ++i) {
				int u = g[s.v][i].first;
				double d = g[s.v][i].second;
				State w(u, s.t, s.g + d);
				if (d == 0) --w.t;
				if (w.t >= 0 and dist[w.v][w.t] > w.g) {
					dist[w.v][w.t] = w.g;
					pq.push(w);
				}
			}
		}

		cout << setprecision(1) << fixed << ans << endl;
	}
}