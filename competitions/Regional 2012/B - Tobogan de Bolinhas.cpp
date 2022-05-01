#include <string>
#include <queue>
#include <algorithm>
#include <vector>
#include <map>
#include <iostream>
#include <iomanip>
#include <set>
#include <cmath>
#include <functional>
#include <cstring>
#include <limits>
#define EPS 1e-9
#define INF (1<<28)
#define pb push_back
#define mp make_pair 

using namespace std;
typedef pair<int, int> ii;

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

int N, L, H;

int main() {
	ios_base::sync_with_stdio(false);
	while(cin>>N){
		cin>>L>>H;
		vector<pair<Point, Point> > aletas;
		for (int i=1;i<=N;++i){
			double yi, xf, yf;
			cin >> yi >> xf >> yf;			
			if (i % 2 != 0) { // impar, esquerda
				aletas.pb(mp(Point(xf, yf), Point(0, yi)));
			} else { // par, direita
				aletas.pb(mp(Point(xf, yf), Point(L, yi)));
			}
		}

		double min_dist = numeric_limits<double>::max();
		for (int i=0;i<N;++i){
			if ((i+1) % 2 != 0) { // impar, esquerda
				min_dist = min(min_dist, 
					dist_line_seg_line_seg(aletas[i].first, aletas[i].second, 
						Point(L, H), Point(L, 0)));
			} else { // par, direita
				min_dist = min(min_dist, 
					dist_line_seg_line_seg(aletas[i].first, aletas[i].second, 
						Point(0, H), Point(0, 0)));
			}
			if (i != N-1) {
				min_dist = 
					min(min_dist, dist_line_seg_line_seg(aletas[i].first, 
						aletas[i].second, aletas[i+1].first, 
						aletas[i+1].second));
			}
		}
		cout << setprecision(2)<<fixed<<min_dist<<endl;
	}
}