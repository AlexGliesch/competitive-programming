#include <queue>
#include <vector>
#include <ciso646>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <limits>
#include <cmath>

using namespace std;
typedef long long ll;

/* 
 * problem solved by modeling the input as a bipartite graph:
 * 
 * players are nodes on one side, and finishing points are nodes at the other 
 * side. a player connects to a given finishing point, if that finishing point
 * accepts the color of that player.
 * 
 * to solve that, we run a min cost max flow (= max bipartite matching). create
 * a source node that connects to all the players with edges of weight 0 and 
 * cap 1. the edges connecting the players to the finishing points have cap 1
 * and weight distance(player, finish) / speed(player). then, all finishing
 * points connect to a target node with weight 0 and cap 1. 
 * 
 * try to send as much flow as you can from source to target, and the total
 * flow will be your answer.
 * 
 * (look at main() to see how i assigned node numbers to solve this)
 *  
 * */

struct MCMF {
	struct Edge {
		ll from, to;
		double cap, flow, wt;
		Edge(ll from, ll to, double cap, double flow, double wt)
			: from(from), to(to), cap(cap), flow(flow), wt(wt) {
		}
	};

	vector<Edge> edge;
	vector<ll> pred, in_queue;
	vector<double> dist;
	vector<vector<ll> > g;
	ll n, s, t;

	MCMF(ll n, ll s, ll t) : n(n), s(s), t(t) { g.resize(n + 10); }

	void add_edge(ll u /* from */, ll v /* to */, double w /* cost */, 
		double c /* capacity */) {
		g[u].push_back(edge.size());
		edge.push_back(Edge(u, v, c, 0, w));
		g[v].push_back(edge.size());
		edge.push_back(Edge(v, u, 0, 0, -w));
	}

	bool spfa() {
		dist.assign(n, numeric_limits<double>::max());
		pred.assign(n, -1);
		in_queue.assign(n, false);
		queue<ll> q; q.push(s);
		dist[s] = 0, in_queue[s] = true;
		while (q.size()) {
			ll v = q.front(); q.pop();
			in_queue[v] = false;
			for (ll i = 0; i < g[v].size(); ++i) {
				ll e = g[v][i];
				if (edge[e].cap - edge[e].flow <= 0) continue;
				ll u = edge[e].to;
				double d = dist[v] + edge[e].wt;
				if (dist[u] > d) {
					dist[u] = d;
					pred[u] = e;
					if (not in_queue[u]) {
						in_queue[u] = true;
						q.push(u);
					}
				}
			}
		}
		return dist[t] != numeric_limits<double>::max();
	}

	double min_cost_max_flow() {
		double total_flow = 0, total_cost = 0;
		while (spfa()) {
			double f = numeric_limits<double>::max();
			for (ll e = pred[t]; e != -1; e = pred[edge[e].from]) {
				f = min(f, edge[e].cap - edge[e].flow);
			}
			if (f == 0) continue;
			for (ll e = pred[t]; e != -1; e = pred[edge[e].from]) {
				edge[e].flow += f;
				edge[e ^ 1].flow -= f;
			}
			total_flow += f;
			total_cost += (f * dist[t]);
		}
		return total_cost;
	}	
};

ll N, M;
double px[110], py[110], fx[110], fy[110], s[110];

double get_time(ll player, ll finish) {
	double dist = sqrt(pow(px[player] - fx[finish], 2) 
		+ pow(py[player] - fy[finish], 2));
	return dist / s[player];
}

int main() {
#define SOURCE 0 /* node 0 -> start */
#define TARGET 1 /* node 1 -> finish */
#define PLAYER(v) (2+v) /* nodes [2..N+1] -> players */
#define FINISH(v) (2+N+v) /* nodes [N+2..M+N+1] -> finish polls */

	while (cin >> N >> M, not(M == 0 and N == 0)) {
		MCMF mcmf(M + N + 2, SOURCE, TARGET);
		
		for (ll i = 0; i < N; ++i) {
			cin >> px[i] >> py[i] >> s[i];
			mcmf.add_edge(SOURCE, PLAYER(i), 0, 1);
		}
		for (ll i = 0, Ci; i < M; ++i) {
			cin >> fx[i] >> fy[i];
			while (cin >> Ci, Ci != 0) {
				mcmf.add_edge(PLAYER(Ci-1), FINISH(i), get_time(Ci-1, i), 1);
			}
			mcmf.add_edge(FINISH(i), TARGET, 0, 1);
		}

		double d = mcmf.min_cost_max_flow();
		cout << setprecision(1) << fixed << d << endl;
	}
}