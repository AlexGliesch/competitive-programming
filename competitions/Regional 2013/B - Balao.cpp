#include <cmath>
#include <vector>
#include <algorithm>
#include <iostream>
#include <limits>
#include <map>

using namespace std;

struct point {
	int x, y;
	bool operator<(const point& p) const {
		return y < p.y or y == p.y and x < p.x;
	}
	point(int x = 0, int y = 0) :x(x), y(y) {}
};

int N, C;

bool sort_pair_points(const pair<point, point>& p1,
                      const pair<point, point>& p2) {
	int minyp1 = max(p1.first.y, p1.second.y);
	int minyp2 = max(p2.first.y, p2.second.y);
	int minxp1 = max(p1.first.x, p1.second.x);
	int minxp2 = max(p2.first.x, p2.second.x);
	return (minyp1 < minyp2 or minyp1 == minyp2 and minxp1 < minxp2);

}

vector<pair<point, point> > pts;
vector<int> minx, miny, maxx, maxy;

double gety(int pi, double x) {
	if (maxy[pi] == miny[pi]) return maxy[pi];
	return miny[pi] +
	       abs(((x - minx[pi]) / (maxx[pi] - minx[pi])) * (maxy[pi] - miny[pi]));
}

map<point, point> dp;

point intersect(point atual, int curi) {
	if (dp.find(atual) != dp.end())
		return dp[atual];

	double besty = numeric_limits<double>::max();
	int besti = -1;
	bool stay = false;
	int stayy = -1;
	for (int i = curi; i<N; ++i) {
		if (miny[i] > besty) break;

		if (atual.x >= minx[i] and atual.x <= maxx[i]) {
			double cy = gety(i, atual.x);
			if (cy > atual.y and cy < besty) {
				besty = cy;
				besti = i;
				if (miny[i] == maxy[i]) {					
					stay = true;
					stayy = miny[i];
				} else {
					stay = false;
				}
			}
		}
	}
	if (besti == -1) {
		return dp[atual] = point(atual.x, -1);
	} else {
		if (stay) return dp[atual] = point(atual.x, stayy);
		else {
			int nexti = curi;
			int nexty = maxy[besti];
			while(maxy[nexti] < nexty) ++nexti;
			if (nexti == curi) ++nexti;

			if (pts[besti].first.y == nexty)
				return dp[atual] = intersect(pts[besti].first, nexti);
			else 
				return dp[atual] = intersect(pts[besti].second, nexti);
		}
	}
}

int main() {
	while (cin >> N >> C) {
		pts.clear();
		pts.resize(N);
		for (int i = 0; i < N; ++i) {
			cin >> pts[i].first.x >> pts[i].first.y >> 
				pts[i].second.x >> pts[i].second.y;
		}
		sort(pts.begin(), pts.end(), sort_pair_points);

		minx.clear(); minx.resize(N + 1);
		miny.clear(); miny.resize(N + 1);
		maxx.clear(); maxx.resize(N + 1);
		maxy.clear(); maxy.resize(N + 1);
		for (int i = 0; i < N; ++i) {
			minx[i] = min(pts[i].first.x, pts[i].second.x);
			miny[i] = min(pts[i].first.y, pts[i].second.y);
			maxx[i] = max(pts[i].first.x, pts[i].second.x);
			maxy[i] = max(pts[i].first.y, pts[i].second.y);
		}

		dp.clear();
		for (int i = 0; i < C; ++i) {
			point p;
			cin >> p.x;
			p.y = 0;
			point res = intersect(p, -1);

			if (res.y == -1) {
				cout << (int)res.x << endl;
			} else {
				cout << (int)res.x << " " << (int)res.y << endl;
			}
		}
	}
}
