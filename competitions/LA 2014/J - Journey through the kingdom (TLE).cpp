#include <queue>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <ciso646>

using namespace std;

int RS, CS, N;
int V[510][510], R[510][510], C[510][510];
int posR[10], posC[10];

struct State {
	int r, c, cost;
	bool operator<(const State& s) const {
		return cost > s.cost;
	}
};

int dijkstra(int Sr, int Sc, int Tr, int Tc) {
	static int dist[510][510];
	memset(dist, -1, sizeof(dist));

	priority_queue<State> pq;
	dist[Sr][Sc] = 0;
	pq.push({ Sr, Sc, 0 });

	while (pq.size()) {
		State s = pq.top(); pq.pop();
		if (dist[s.r][s.c] != s.cost)
			continue;

		if (s.r == Tr and s.c == Tc) return s.cost;

		for (int r = max(0, s.r - R[s.r][s.c]);
			r <= min(RS - 1, s.r + R[s.r][s.c]); ++r) {
			for (int c = max(0, s.c - C[s.r][s.c]);
				c <= min(CS - 1, s.c + C[s.r][s.c]); ++c) {
				/*cout << "from (" << s.r << ", " << s.c << ") to ("
				<< r << ", " << c << ")" << endl;*/
				if (dist[r][c] == -1 or dist[r][c] > s.cost + V[s.r][s.c]) {
					dist[r][c] = s.cost + V[s.r][s.c];
					pq.push({ r, c, dist[r][c] });
				}
			}
		}
	}

	return -1;
}

int main() {
	ios_base::sync_with_stdio(false);
	while (cin >> RS >> CS >> N) {
		for (int r = 0; r < RS; ++r)
			for (int c = 0; c < CS; ++c)
				cin >> V[r][c];

		for (int r = 0; r < RS; ++r)
			for (int c = 0; c < CS; ++c)
				cin >> R[r][c];

		for (int r = 0; r < RS; ++r)
			for (int c = 0; c < CS; ++c)
				cin >> C[r][c];

		for (int i = 0; i < N; ++i) {
			int r, c; cin >> r >> c;
			posR[i] = r - 1;
			posC[i] = c - 1;
		}

		for (int i = 0; i < N - 1; ++i) {
			if (i) cout << " ";
			cout << dijkstra(posR[i], posC[i], posR[i + 1], posC[i + 1]);
			//break;
		}
		cout << endl;
	}
}