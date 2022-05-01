#include <iostream>
#include <vector>
#include <algorithm>
#include <ciso646>
#include <iomanip>

using namespace std;

/* It's simple once you have the code for the closest pair algorithm.
 * I got it from the internet and implemented myself.
 * 
 * There's still room for optimization, probably.*/

struct Point {
	double x, y;
};

double dist2(const Point& a, const Point& b) {
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

double closest_pair(const vector<Point>& P, int s, int e) {
	if (e - s <= 1) return numeric_limits<double>::max();
	if (e - s == 2) return dist2(P[s], P[s + 1]);
	if (e - s == 3) {
		return min(min(dist2(P[s], P[s + 1]), dist2(P[s + 1], P[s + 2])),
			dist2(P[s], P[s + 2]));
	}
	int mid = (s + (e - s) / 2);
	double d = min(closest_pair(P, s, mid), closest_pair(P, mid, e));

	auto l = upper_bound(begin(P) + s, begin(P) + mid, 
		Point{ abs(P[mid].x - d), 0 }, [&](const Point& p1, const Point& p2) {
		return abs(p1.x - P[mid].x) > abs(p2.x - P[mid].x);	
	});

	auto u = lower_bound(begin(P) + mid, begin(P) + e, 
		Point{ abs(P[mid].x - d), 0 }, [&](const Point& p1, const Point& p2) {
		return abs(p1.x - P[mid].x) < abs(p2.x - P[mid].x);	
	});

	vector<Point> Q(l, u);
	sort(begin(Q), end(Q), [](const Point& p1, const Point& p2) {
		return p1.y < p2.y;	
	});

	auto best = d;
	for (int i = 0; i < Q.size(); ++i) {
		for (int j = i + 1; j < Q.size() and Q[j].y - Q[i].y < d; ++j)
			best = min(dist2(Q[i], Q[j]), best);
	}
	return best;
}

int main() {
	ios_base::sync_with_stdio(false);
	int N;
	vector<Point> P;
	while (cin >> N, N) {
		P.resize(N);
		for (int i = 0; i < N; ++i)
			cin >> P[i].x >> P[i].y;

		sort(begin(P), end(P), [](const Point& p1, const Point& p2) {
			return p1.x < p2.x;
		});

		double d = sqrt(double(closest_pair(P, 0, P.size())));
		if (d >= 10000.0) cout << "INFINITY" << endl;
		else cout << setprecision(4) << fixed << d << endl;
	}
}

