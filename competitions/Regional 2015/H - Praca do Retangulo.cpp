#include <algorithm>
#include <iostream>
#include <ciso646>

using namespace std;

struct Point {
	int x, y;
	bool operator<(const Point& p) const { return x < p.x; }
};

Point P[3010];
int N;

int main() {
	ios_base::sync_with_stdio(false);
	while (cin >> N) {
		for (int i = 0; i < N; ++i) 
			cin >> P[i].x >> P[i].y;
		sort(P, P + N);
		int ans = 0;
		for (int i = 0; i < N; ++i) {
			int high = (1 << 30), low = -high;
			for (int j = i + 1; j < N; ++j) {
				if (P[j].y < low or P[j].y > high) continue;
				if (P[j].y > P[i].y) high = min(high, P[j].y);
				else low = max(low, P[j].y);
				++ans;
			}
		}
		cout << ans << endl;
	}	
}