#include <algorithm>
#include <vector>
#include <queue>
#include <iostream>
#include <functional>
using namespace std;

/*
 *	generate a graph for the input; when a line goes through
 *	nodes x1, x2, ..., xn, create all possible pairs of edges between those
 *	nodes. Bus line edges always have weight 0, and train edges have weight 
 *	4 when connecting to a different zone, otherwise 0.
 *	
 *	an edge also has a unique line_id identifier, which is different for every
 *	train or line, and a flag saying whether it is a bus or a train line.
 *	
 *	run Dijkstra on the graph, and add to the result the initial cost to enter
 *	the system (2). When visiting an edge on Dijkstra, if that edge is a bus,
 *	and represents a different line then the last edge expanded, then add 1 to 
 *	the edge weight.	
*/

enum { Train = 0, Bus = 1 };

struct Edge {
	int v, w, line, ttype;
	Edge(int v, int w, int ttype = -1, int line = -1) 
		: v(v), w(w), ttype(ttype), line(line) {}
	bool operator<(const Edge& e) const {
		return w > e.w;
	}
};

int Z, S, T, B, X, Y, line_id = 0;
vector<int> zone;
vector<vector<Edge> > g;

int dijkstra() {
	vector<int> dist(S + 1, -1);
	dist[X] = 2;
	priority_queue<Edge> pq;
	pq.push(Edge(X, 2));
	
	while (pq.size()) {
		Edge cur = pq.top(); pq.pop();
		if (cur.v == Y) return cur.w;
		if (dist[cur.v] != cur.w) continue;
		for (int i = 0; i < g[cur.v].size(); ++i) {
			Edge& e = g[cur.v][i];
			int tw = e.w + cur.w, u = e.v;
			if (e.line != cur.line and e.ttype == Bus) ++tw;
			if (dist[u] == -1 or dist[u] > tw) {
				dist[u] = tw;
				pq.push(Edge(e.v, tw, e.ttype, e.line));
			}
		}
	}

	return -1;
}

int main() {
	while (cin >> Z >> S, Z and S) {
		zone.assign(S + 1, 0);
		for (int i = 0; i < Z; ++i) {
			int K; cin >> K;
			for (int j = 0; j < K; ++j) {
				int s; cin >> s; zone[s] = i;
			}
		}

		cin >> T >> B;
		g.clear(); g.resize(S + 1);

		/* train itinerary */
		for (int i = 0; i < T; ++i) {
			int L; cin >> L;
			vector<int> it(L);
			for (int j = 0; j < L; ++j) cin >> it[j];

			vector<int> dd(L, 0);
			int dist = 0;
			for (int j = 1; j < L; ++j) {
				if (zone[it[j]] != zone[it[j - 1]]) dist += 4;
				dd[j] = dist;
			}

			for (int n = 0; n < L; ++n) {
				for (int m = n + 1; m < L; ++m) {
					int w = dd[m] - dd[n];
					g[it[n]].push_back(Edge(it[m], w, Train, line_id));
					g[it[m]].push_back(Edge(it[n], w, Train, line_id));
				}
			}
			++line_id;
		}

		/* bus itinerary */
		for (int i = 0; i < B; ++i) {
			int L; cin >> L;
			vector<int> it(L);
			for (int j = 0; j < L; ++j) {
				cin >> it[j];
			}

			for (int n = 0; n < L; ++n) {
				for (int m = n + 1; m < L; ++m) {
					g[it[n]].push_back(Edge(it[m], 0, Bus, line_id));
					g[it[m]].push_back(Edge(it[n], 0, Bus, line_id));

				}
			}
			++line_id;
		}

		cin >> X >> Y;
		cout << dijkstra() << endl;
	}
}