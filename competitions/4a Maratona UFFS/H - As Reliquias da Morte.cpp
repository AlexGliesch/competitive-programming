#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>
#include <ciso646>
#include <queue>
#include <functional>
#define EPS 1e-10

using namespace std;

struct Point { 
	Point(double x = 0, double y = 0) : x(x), y(y) { }
	double x, y; 
};

/* 
 * Distance of two points in 2D.
 * */
double dist(const Point& a, const Point& b) {
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

/* 
 * Distance of point p to line defined by AB. Closest point on AB is returned on 
 * 'ret'.
 * */
double dist_to_line(const Point& p, const Point& A, const Point& B, 
					Point* ret = NULL) {
	double scale = double((p.x - A.x) * (B.x - A.x) + (p.y - A.y) * (B.y - A.y))
		/ ((B.x - A.x) * (B.x - A.x) + (B.y - A.y) * (B.y - A.y));
	Point r(A.x + scale * (B.x - A.x), A.y + scale * (B.y - A.y));
	if (ret) *ret = r;
	return dist(p, r);
}

/* 
 * Distance of point p to line segment defined by AB. The closest point on AB is 
 * returned on 'ret'.
 * */
double dist_to_line_segment(const Point& p, const Point& A, const Point& B, 
							Point* ret = NULL) {
	if ((B.x - A.x) * (p.x - A.x) + (B.y - A.y) * (p.y - A.y) < EPS) {
		if (ret) *ret = A;
		return dist(p, A);
	} else if ((A.x - B.x) * (p.x - B.x) + (A.y - B.y) * (p.y - B.y) < EPS) {
		if (ret) *ret = B;
		return dist(p, B);
	} else {
		return dist_to_line(p, A, B, ret);
	}
}

bool in_range(const Point& p, const Point& q, const Point& r) {
	return r.x <= max(p.x, q.x) and r.x >= min(p.x, q.x)
		and r.y <= max(p.y, q.y) and r.y >= min(p.y, q.y);
}

/* 
 * Returns true if line segments intersect. The intersection is returned to 
 * ret, if there is exactly one intersection.
 * */
bool line_segments_intersect(const Point& p1, const Point& q1,
							 const Point& p2, const Point& q2, 
							 Point* ret = NULL) {
	double a1 = q1.y - p1.y, b1 = p1.x - q1.x, c1 = a1 * p1.x + b1 * p1.y;
	double a2 = q2.y - p2.y, b2 = p2.x - q2.x, c2 = a2 * p2.x + b2 * p2.y;
	double det = a1 * b2 - a2 * b1;
	if (abs(det) < EPS) { /* Lines are parallel */
		return in_range(p1, q1, p2) or in_range(p1, q1, q2)
			or in_range(p2, q2, p1) or in_range(p2, q2, q1);
	}
	Point r((b2 * c1 - b1 * c2) / det, (a1 * c2 - a2 * c1) / det);
	bool ans = in_range(p1, q1, r) and in_range(p2, q2, r);
	if (ans and ret) *ret = r;
	return ans;
}

/* 
 * Minimum distance between two line segments AB and BC. If AB and BC intersect,
 * the minimum distance is 0. Otherwise, it's the min between distance of 
 * A to CD, of B to CD, of C to AB, or of D to AB.
 * */
double dist_line_seg_line_seg(const Point& A, const Point& B,
							  const Point& C, const Point& D) {
	if (line_segments_intersect(A, B, C, D)) return 0;
	double dACD = dist_to_line_segment(A, C, D);
	double dBCD = dist_to_line_segment(B, C, D);
	double dCAB = dist_to_line_segment(C, A, B);
	double dDAB = dist_to_line_segment(D, A, B);
	return min(min(dACD, dBCD), min(dCAB, dDAB));
}

double prim(vector<vector<double> >& g) {
	vector<bool> taken(g.size(), false);
	priority_queue<pair<double, int>, vector<pair<double, int> >,
		greater<pair<double, int> > > pq;
	double cost = 0;
	taken[0] = true;

	for (int v = 1; v < g.size(); ++v)
		pq.push(make_pair(g[0][v], v));

	while (pq.size()) {
		int u = pq.top().second; 
		double w = pq.top().first; pq.pop();
		if (taken[u]) continue;
		taken[u] = true;
		cost += w;
		for (int v = 0; v < g.size(); ++v) {
			if (!taken[v]) pq.push(make_pair(g[u][v], v));
		}
	}
	return cost;
}

int main() {
	ios_base::sync_with_stdio(false);
	int N; cin >> N;
	vector<vector<double> > g(N, vector<double>(N, 0));
	vector<pair<Point, Point> > lines(N);
	for (int i = 0; i < N; ++i) {
		cin >> lines[i].first.x >> lines[i].first.y
			>> lines[i].second.x >> lines[i].second.y;
	}
	for (int i = 0; i < N; ++i) {
		for (int j = i + 1; j < N; ++j) {
			g[i][j] = g[j][i] = dist_line_seg_line_seg(
				lines[i].first, lines[i].second,
				lines[j].first, lines[j].second);
		}
	}

	//cout << "prim:" << endl;
	cout << ceil(prim(g)) << endl;
}