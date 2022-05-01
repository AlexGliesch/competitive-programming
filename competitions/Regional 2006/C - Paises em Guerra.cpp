#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;
typedef long long ll;

/*
 * a normal shortest paths problem. the problem does not specify this fully, 
 * but, if for any two nodes A and B, there is a path from node A to node B 
 * and a  path from B to A, then, if they have a direct edge, its distance is 0.
 *
 * in order to check that, run a dfs from every node and check which nodes
 * were visited. for every node visited, if that node also visited the current
 * one, their distance will be 0.
 *
 * ps: use dijkstra, because floyd-warshall will get you TLE!
 *
 * */

ll n, e, dist[510], visited[510][510];
vector<vector<pair<ll, ll> > > g;

void dfs(ll v, ll from) {
	if (visited[from][v]) return;
	visited[from][v] = true;
	if (visited[v][from]) {
		for (int i = 0; i < g[v].size(); ++i) {			
			if (g[v][i].second == from) {
				g[v][i].first = 0;
				break;
			}
		}
		for (int i = 0; i < g[from].size(); ++i) {
			if (g[from][i].second == v) {
				g[from][i].first = 0;
				break;
			}
		}
	}
	for (ll i = 0; i < g[v].size(); ++i) {
		if (not visited[from][g[v][i].second]) 
			dfs(g[v][i].second, from);
	}
}

ll dijkstra(ll s, ll t) {
	memset(dist, -1, sizeof(dist));
	priority_queue<pair<ll, ll> > pq;
	dist[s] = 0;
	pq.push(make_pair(0, s));
	while (pq.size()) {
		ll v = pq.top().second, w = -pq.top().first;
		pq.pop();
		if (dist[v] != w) continue;
		if (v == t) return w;
		for (ll i = 0; i < g[v].size(); ++i) {
			ll u = g[v][i].second, cd = g[v][i].first + w;
			if (dist[u] == -1 or dist[u] > cd) {
				dist[u] = cd;
				pq.push(make_pair(-cd, u));
			}
		}
	}
	return -1;
}

int main() {
	while (cin >> n >> e) {
		if (n == 0) break;

		g.clear(); g.resize(n);
		for (ll i = 0; i < e; ++i) {
			ll x, y, h; cin >> x >> y >> h;
			--x,--y;
			g[x].push_back(make_pair(h, y));
		}

		memset(visited, 0, sizeof(visited));
		for (ll i = 0; i < n; ++i) dfs(i, i);

		ll k; cin >> k;
		for (ll i = 0; i < k; ++i) {
			ll o, d; cin >> o >> d;
			--o, --d;

			ll x = dijkstra(o, d);
			if (x == -1) cout << "Nao e possivel entregar a carta" << endl;
			else cout << x << endl;
		}
		cout << endl;
	}
}