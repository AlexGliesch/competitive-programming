#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <queue>
#include <ciso646>
#include <functional>
#define EPS 1e-9

using namespace std;

/*
 * the path will always go through the edges of the obstacles, and the first
 * (initial) and last (goal) points. therefore, those points can be seen as
 * nodes in a graph. there is an edge between point A and B if there is no
 * obstacle intersecting the line that connects A and B; the edge weight is
 * the Euclidean distance between A and B.
 *
 * having generated the graph, run Dijkstra and you're done.
 * */

struct Point {
	Point(double x = 0, double y = 0) : x(x), y(y) { }
	bool operator==(const Point& p) const {
		return abs(x - p.x) < EPS and abs(y - p.y) < EPS;
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
	Point r((b2 * c1 - b1 * c2) / det, (a1 * c2 - a2 * c1) / det );
	return in_range(p1, q1, r) and in_range(p2, q2, r);
}

double dist(const Point& a, const Point& b) {
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int main() {
	int Xi, Yi, Xf, Yf, n;
	while (cin >> Xi >> Yi >> Xf >> Yf >> n) {
		if (Xi == 0 and Yi == 0 and Xf == 0 and Yf == 0 and n == 0) break;
		vector<Point> P; /* P[0] = initial, P[1] = final */
		P.push_back(Point(Xi, Yi));
		P.push_back(Point(Xf, Yf));

		vector<Point> L1(n), L2(n); /* points 1 and 2 of the lines. */
		for (int i = 0; i < n; ++i) {
			cin >> L1[i].x >> L1[i].y >> L2[i].x >> L2[i].y;
			P.push_back(L1[i]);
			P.push_back(L2[i]);
		}

		/* create graph */
		vector<vector<pair<double, int> > > g(P.size() + 1);
		for (int i = 0; i < P.size(); ++i) {
			const Point& v = P[i];
			for (int j = 0; j < P.size(); ++j) {
				const Point& u = P[j];
				if (u != v) {
					bool has_obstacle = false;
					for (int k = 0; k < n; ++k) {
						if (u != L1[k] and u != L2[k] and
							v != L1[k] and v != L2[k] and
							line_segments_intersect(u, v, L1[k], L2[k])) {
							has_obstacle = true;
							break;
						}
					}
					if (not has_obstacle) {
						double d = dist(u, v);
						g[i].push_back(make_pair(d, j));
						g[j].push_back(make_pair(d, i));						
					}
				}
			}
		}

		/* run dijkstra */
		priority_queue < pair<double, int>, vector<pair<double, int> >,
			greater<pair<double, int> > > pq;
		vector<double> dist(g.size(), -1);
		dist[0] = 0;
		pq.push(make_pair(0, 0));
		while (pq.size()) {			
			double d = pq.top().first;
			int v = pq.top().second; pq.pop();
			if (dist[v] != d) continue;
			if (v == 1) break;
			for (int i = 0; i < g[v].size(); ++i) {
				int u = g[v][i].second;
				double cd = g[v][i].first + d;
				if (dist[u] == -1 or dist[u] > cd) {
					dist[u] = cd;
					pq.push(make_pair(cd, u));
				}
			}
		}

		cout << setprecision(2) << fixed << dist[1] << endl;
	}
}