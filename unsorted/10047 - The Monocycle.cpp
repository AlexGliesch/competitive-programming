#include <ciso646>
#include <cstring>
#include <functional>
#include <iostream>
#include <queue>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

/*
* we can represent a node in the search space by a tuple
* (row, column, wheel position, facing direction).
*
* the initial state has the row/column where S is, with wheel position 0 and
* facing direction 1. the final states have the position where T is, wheel
* position 0, and all facing directions possible (there is more than 1
* final state).
*
* the neighbours of a state are all the adjacent available rows and columns,
* with wheel position = (1 + current wheel position) % 5, and facing direction
* corresponding to the direction used to move to that adjacent position
* (see dc[] and dr[] in the code for more detail).
*
* considering this search space, just do a dijkstra and it will give you the
* solution.
* */

int m, n, dc[] = {0, 0, 1, -1}, dr[] = {1, -1, 0, 0};
vector<string> g;
int sr, sc, tr, tc, dist[25][25][5][4], sw = 0, sf = 1;

bool valid(int ur, int uc) {
	return ur >= 0 and ur < m and uc >= 0 and uc < n and g[ur][uc] != '#';
}

int dijkstra() {
	priority_queue<pair<int, tuple<int, int, int, int>>> pq;
	auto s = make_tuple(sr, sc, sw, sf);
	dist[sr][sc][sw][sf] = 0;
	pq.emplace(0, s);
	while (pq.size()) {
		auto v = pq.top().second;
		int vd = -pq.top().first;
		pq.pop();
		int vr = get<0>(v), vc = get<1>(v), vf = get<3>(v), vw = get<2>(v);
		if (vr == tr and vc == tc and vw == 0)
			return vd;
		for (int uf = 0; uf < 4; ++uf) {
			int ur = vr + dr[uf], uc = vc + dc[uf], uw = (vw + 1) % 5;
			auto u = make_tuple(ur, uc, uw, uf);
			if (valid(ur, uc)) {
				int ud = 1 + vd;
				if (uf == 0 and vf == 1 or uf == 1 and vf == 0 or uf == 2 and vf == 3 or
					uf == 3 and vf == 2)
					ud += 2;
				else if (uf != vf)
					ud += 1;
				if (dist[ur][uc][uw][uf] == -1 or dist[ur][uc][uw][uf] > ud) {
					pq.emplace(-(dist[ur][uc][uw][uf] = ud), u);
				}
			}
		}
	}
	return -1;
}

int main() {
	ios_base::sync_with_stdio(false);
	int t = 1;
	while (cin >> m >> n, m and n) {
		g.clear();
		string s;
		getline(cin, s);
		for (int i = 0; i < m; ++i) {
			getline(cin, s);
			g.push_back(s);
		}
		for (int r = 0; r < m; ++r) {
			for (int c = 0; c < n; ++c) {
				if (g[r][c] == 'S')
					sr = r, sc = c;
				else if (g[r][c] == 'T')
					tr = r, tc = c;
			}
		}
		memset(dist, -1, sizeof dist);
		if (t > 1)
			cout << endl;
		cout << "Case #" << t++ << endl;
		int ans = dijkstra();
		if (ans == -1) {
			cout << "destination not reachable" << endl;
		} else {
			cout << "minimum time = " << ans << " sec" << endl;
		}
	}
}