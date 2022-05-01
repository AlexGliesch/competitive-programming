#include <map>
#include <string>
#include <queue>
#include <vector>
#include <algorithm>
#include <iostream>
#include <ciso646>
#include <unordered_map>
#include <cstring>
#include <tuple>
#define mp make_pair

/*
 * Dijkstra, each language is a vertex, and each word connecting two
 * languages is an edge. The search state is a pair of integers: the current
 * vertex and the first character of the current word.
 * 
 * ps: after some optimizations, rank 1! :D
 **/

using namespace std;

struct Edge {
	Edge(short v, short word_size, short first_char)
		: v(v), word_size(word_size), first_char(first_char) {
	}
	short v, word_size, first_char;
};

int M, S, T, dist[2010][30];
unordered_map<string, int> strtoi;
vector<vector<Edge> > g;

int dijkstra() {
	priority_queue<tuple<int, short, short> > pq;
	memset(dist, -1, sizeof dist);
	dist[S]['z' + 1] = 0;
	pq.emplace(0, S, 'z' + 1);

	while (pq.size()) {
		int d = -get<0>(pq.top());
		short v = get<1>(pq.top()), first_char = get<2>(pq.top());
		pq.pop();

		if (d != dist[v][first_char]) continue;
		if (v == T) return d;
		for (int i = 0; i < g[v].size(); ++i) {
			Edge& u = g[v][i];
			if (u.first_char == first_char) continue;
			int cd = d + u.word_size;
			if (dist[u.v][u.first_char] == -1 or dist[u.v][u.first_char] > cd) {
				dist[u.v][u.first_char] = cd;
				pq.emplace(-cd, u.v, u.first_char);
			}
		}
	}
	return -1;
}

int main() {
	ios_base::sync_with_stdio(false);
	while (cin >> M, M) {
		g.clear();
		strtoi.clear();
		int counter = 0;
		string O, D; cin >> O >> D;
		for (int i = 0; i < M; ++i) {
			string I1, I2, P; cin >> I1 >> I2 >> P;
			if (strtoi.find(I1) == strtoi.end()) {
				strtoi[I1] = counter++;
				g.push_back(vector<Edge>());
			}
			if (strtoi.find(I2) == strtoi.end()) {
				strtoi[I2] = counter++;
				g.push_back(vector<Edge>());
			}

			g[strtoi[I1]].push_back(Edge(strtoi[I2], P.size(), P[0]));
			g[strtoi[I2]].push_back(Edge(strtoi[I1], P.size(), P[0]));
		}

		if (not strtoi.count(O) or not strtoi.count(D)) {
			cout << "impossivel" << endl;
			continue;
		}

		S = strtoi[O], T = strtoi[D];
		int ans = dijkstra();
		if (ans == -1) {
			cout << "impossivel" << endl;
		} else {
			cout << ans << endl;
		}
	}
}