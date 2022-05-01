#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <ciso646>
#include <string>
#include <cstring>
using namespace std;

struct State {
	State(int r, int c, int keys = 0) : r(r), c(c), keys(keys) {}
	int keys;
	int r, c;
	bool operator<(const State& s) const {
		return r < s.r or r == s.r and c < s.c or r == s.r and c == s.c
			and keys < s.keys;
	}
};

int R, C;
int rs, cs, rf, cf;
int dr[] = { 0, 0, -1, 1 };
int dc[] = { -1, 1, 0, 0 };

bool valid(int r, int c) {
	return r >= 0 and r < R and c >= 0 and c < C;
}

int main() {
	vector<string> g;
	string s;
	while (cin >> s) {
		g.push_back(s);
	}
	R = g.size(), C = g[0].size();
	for (int i = 0; i < R; ++i) {
		for (int j = 0; j < C; ++j) {
			if (g[i][j] == '@') {
				rs = i, cs = j;
				break;
			}
		}
	}

	vector<vector<vector<int>>> dist(110, 
		vector<vector<int>>(110, vector<int>(300, -1)));
	dist[rs][cs][0] = 0;

	priority_queue<pair<int, State>> pq;
	pq.emplace(0, State(rs, cs, 0));
	while (pq.size()) {
		int d = -pq.top().first;
		State s = pq.top().second;
		pq.pop();

		if (dist[s.r][s.c][s.keys] != d) continue;
		if (g[s.r][s.c] == '*') {
			cout << d << endl;
			return 0;
		}

		for (int i = 0; i < 4; ++i) {
			int nr = s.r + dr[i], nc = s.c + dc[i];
			int nk = s.keys;
			int cd = d + 1;
			if (not valid(nr, nc)) continue;
			char c = g[nr][nc];

			if (c >= 'A' and c <= 'G') {
				if (not (s.keys & (1 << (c - 'A')))) continue;
			}
				
			if (c == '#') {
				continue;
			}

			if (c >= 'a' and c <= 'g')
				nk |= (1 << (c - 'a'));

			if (dist[nr][nc][nk] == -1 or dist[nr][nc][nk] > cd) {
				dist[nr][nc][nk] = cd;
				pq.emplace(-cd, State(nr, nc, nk));
			}
		}
	}
	cout << "--" << endl;
	return 0;
}