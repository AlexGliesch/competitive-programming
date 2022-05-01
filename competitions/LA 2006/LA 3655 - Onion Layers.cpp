#include <iostream>
#include <ciso646>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

/* looking at the image, it's easy to see it's a convex hull problem. */

struct Point {
	int x, y;

	bool operator<(const Point& p) const {
		return x < p.x or(x == p.x and y < p.y);
	}
	bool operator==(const Point& p) const { return p.x == x and p.y == y; }
};

/*  > 0 ccw
*  < 0 cw
*  = 0 collinear*/
int cross(const Point& p, const Point& q, const Point& r) {
	return (q.x - p.x) * (r.y - p.y) - (q.y - p.y) * (r.x - p.x);
}

vector<Point> convex_hull(vector<Point> P) {
	int n = P.size(), k = 0;
	vector<Point> H(2 * n);

	sort(P.begin(), P.end());

	for (int i = 0; i < n; i++) {
		while (k >= 2 and cross(H[k - 2], H[k - 1], P[i]) < 0) k--;
		H[k++] = P[i];
	}

	for (int i = n - 2, t = k + 1; i >= 0; i--) {
		while (k >= t and cross(H[k - 2], H[k - 1], P[i]) < 0) k--;
		H[k++] = P[i];
	}

	H.resize(k);
	return H;
}

int main() {
	while (true) {
		int N; cin >> N;
		if (N == 0) break;

		vector<Point> P(N);
		for (int i = 0; i < N; ++i) {
			cin >> P[i].x >> P[i].y;
		}

		int layers = 0;
		while (P.size() > 0) {
			vector<Point> hull = convex_hull(P);
			for (int i = 0; i < hull.size(); ++i) {
				vector<Point>::iterator it = find(P.begin(), P.end(), hull[i]);
				if (it != P.end()) P.erase(it);
			}
			++layers;
		}

		if (layers % 2 == 0) {
			cout << "Do not take this onion to the lab!" << endl;
		} else {
			cout << "Take this onion to the lab!" << endl;
		}
	}
}