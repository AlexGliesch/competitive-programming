#include <vector>
#include <algorithm>
#include <queue>
#include <ciso646>
#include <string>
#include <iostream>
#include <map>

using namespace std;

/* This problem is quite simple and can be solved with Bipartite Matching. In
 * particular, I solved the matching problem by transforming it in a maximum
 * flow problem, which is solved by the push-relabel algorithm.
 * 
 * Every t-shirt size is a node. Every volunteer is also a node.
 * The t-shirt sizes are connected to volunteers who can wear them, with an 
 * edge of weight 1.
 * Each t-shirt size is connected to the source node with weight N/6 (number of
 * t-shirts available).
 * Each volunteer is connected to the target node with weight 1.
 * 
 * Run max flow and see if it is equal to M, if so print YES, otherwise 
 * print NO.
 * */

struct PushRelabelMaxFlow {
	struct Edge { 
		Edge(int from, int to, int cap, int flow)
			: from(from), to(to), cap(cap), flow(flow) { }
		int from, to, cap, flow; 
	};
	vector<Edge> edge;
	vector<vector<int> > g;
	int n, s, t;
	vector<int> excess, dist, active, ct;
	queue<int> q;

	PushRelabelMaxFlow(int n, int s, int t) :n(n), s(s), t(t) {
		g.resize(n); 
	}

	void add_edge(int u, int v, int c) {
		g[u].push_back(edge.size());
		edge.push_back(Edge(u, v, c, 0));
		g[v].push_back(edge.size());
		edge.push_back(Edge(v, u, 0, 0));
	}

	void enqueue(int v) {
		if (not active[v] and excess[v] > 0) {
			active[v] = true;
			q.push(v);
		}
	}

	void push(int e) {
		int amt = min(excess[edge[e].from], edge[e].cap - edge[e].flow);
		if (dist[edge[e].from] <= dist[edge[e].to] or amt == 0) return;
		edge[e].flow += amt;
		edge[e ^ 1].flow -= amt;
		excess[edge[e].to] += amt;
		excess[edge[e].from] -= amt;
		enqueue(edge[e].to);
	}

	void gap(int k) {
		for (int v = 0; v < n; ++v) {
			if (dist[v] < k) continue;
			--ct[dist[v]];
			dist[v] = max(dist[v], n + 1);
			++ct[dist[v]];
			enqueue(v);
		}
	}

	void relabel(int v) {
		--ct[dist[v]];
		dist[v] = 2 * n;
		for (int i = 0; i < g[v].size(); ++i) {
			int e = g[v][i];
			if (edge[e].cap - edge[e].flow > 0)
				dist[v] = min(dist[v], dist[edge[e].to] + 1);
		}
		++ct[dist[v]];
		enqueue(v);
	}

	void discharge(int v) {
		for (int i = 0; excess[v] > 0 and i < g[v].size(); ++i)
			push(g[v][i]);
		if (excess[v] > 0) {
			if (ct[dist[v]] == 1) gap(dist[v]);
			else relabel(v);
		}
	}

	int push_relabel_max_flow() {
		excess.assign(n, 0);
		dist.assign(n, 0);
		active.assign(n, 0);
		ct.assign(2 * n, 0);

		ct[0] = n - 1;
		ct[n] = 1;
		dist[s] = n;
		active[s] = active[t] = true;

		for (int i = 0; i < g[s].size(); ++i) {
			int e = g[s][i];
			excess[s] += edge[e].cap;
			push(e);
		}

		while (q.size()) {
			int v = q.front(); q.pop();
			active[v] = false;
			discharge(v);
		}

		int flow = 0;
		for (int i = 0; i < g[s].size(); ++i) {
			int e = g[s][i];
			flow += edge[e].flow;
		}
		return flow;
	}
};

int main() {
	ios_base::sync_with_stdio(false);
	int T; cin >> T;

	map<string, int> t_sizes;
	t_sizes.insert(make_pair("XXL", 0));
	t_sizes.insert(make_pair("XL", 1));
	t_sizes.insert(make_pair("L", 2));
	t_sizes.insert(make_pair("M", 3));
	t_sizes.insert(make_pair("S", 4));
	t_sizes.insert(make_pair("XS", 5));

	while (T--) {
		int N, M; cin >> N >> M;
		int n = 2 + 6 + M; /* 2 for source and dest, 6 for the sizes, and M
							 for the volunteers. */
		PushRelabelMaxFlow pr(n, n - 2, n - 1);

		for (int i = 0; i < 6; ++i) {			
			pr.add_edge(pr.s, i, N / 6); /* Edges from "size nodes" to 
										 source. */
		}
		for (int i = 0; i < M; ++i) {
			string s1, s2; cin >> s1 >> s2;
			pr.add_edge(t_sizes[s1], 6 + i, 1);
			pr.add_edge(t_sizes[s2], 6 + i, 1);
			pr.add_edge(6 + i, pr.t, 1); /* Edges from "volunteer nodes"
											  to target */
		}
		int pp = pr.push_relabel_max_flow();
		
		cout << (pp == M ? "YES" : "NO") << endl;
	}
}