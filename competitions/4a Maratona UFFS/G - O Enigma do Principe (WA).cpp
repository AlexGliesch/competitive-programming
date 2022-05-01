#include <iostream>
#include <algorithm>
#include <ciso646>
#include <array>
#include <queue>
#include <map>
#include <string>
#define index(r, c) (((r)*(C))+(c))
#define row(i) (((i)/(C)))
#define col(i) (((i)%(C)))

using namespace std;
using Table = array<char, 21>;

int dc[] = { 0, 0, -1, 1 }, dr[] = { -1, 1, 0, 0 };
int R, C;
Table initial_t;

struct AStarState {
	int h = 0, g = 0;
	int f() const { return g + h; }
	Table t;
};

struct MapCmp {
	bool operator()(const AStarState& a, const AStarState& b) const {
		return a.t < b.t;
	}
};

struct PqCmp {
	bool operator()(const AStarState& a, const AStarState& b) const {
		return a.f() > b.f();
	}
};

int heuristic(const AStarState& a) {
	int num = 0, ct = 0;
	for (int i = 0; i < R*C; ++i) {
		if (not(num & (1 << a.t[i]))) {
			++ct;
			num |= (1 << a.t[i]);
		}
	}
	return ct - 1;
}

void flood(Table& t, int r, int c, int old_color, int new_color, int& visited) {
	int irc = index(r, c);
	if (visited & (1 << irc)) return;
	if (r < 0 or r >= R or c < 0 or c >= C) return;
	if (t[irc] != old_color and t[irc] != new_color) return;
	visited |= (1 << irc);
	t[irc] = new_color;
	for (int i = 0; i < 4; ++i) {
		flood(t, r + dr[i], c + dc[i], old_color, new_color, visited);
	}
}

int a_star() {
	priority_queue<AStarState, vector<AStarState>, PqCmp> pq;
	map<AStarState, int, MapCmp> dist;
	//map<AStarState, AStarState, MapCmp> pred;
	AStarState a; 
	a.t = initial_t;
	a.h = heuristic(a);
	dist[a] = a.g;

	pq.push(move(a));	
	while (pq.size()) {
		a = pq.top(); pq.pop();
		if (dist[a] != a.g) continue;

		if (a.h == 0) return a.g;
		for (int i = 0; i < R*C; ++i) {
			if (a.t[i] != a.t[0]) {
				auto b = a;
				int v = 0;
				flood(b.t, 0, 0, a.t[0], a.t[i], v);
				b.g = a.g + 1;
				b.h = heuristic(b);
				if (b.h == 0) return b.g;
				
				if (dist.find(b) == dist.end() or dist[b] > b.g) {
					dist[b] = b.g;
					//pred[b] = a;
					pq.push(move(b));
				}
			}
		}
	}	
	return 0;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin >> R >> C;
	string s;
	for (int i = 0; i < R; ++i) {
		cin >> s;
		for (int j = 0; j < C; ++j) 
			initial_t[index(i, j)] = s[j] - '0';
	}
	cout << a_star() << endl;
}