#include <vector>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <ciso646>

using namespace std;

/*
 * The idea: create a spanning tree by starting a dfs from any node v. Any node
 * u can reach any other node, if it can reach v, after the fiber directions 
 * have been set by the spanning tree (that is, because v can definitely reach
 * every other node, so if u can reach v, therefore u can reach any other 
 * node!).
 * 
 * In order to speed this up, after doing the first dfs on an arbitrary node 
 * (I chose node 0), you do a REVERSE dfs on the same node (on the reverse
 * graph, that is, only using fibers that are either free or disabled), and
 * see if it can reach every other node. If yes, then return YES, otherwise,
 * return NO.
 **/

enum State { Enabled = 1, Disabled = 2, Either = 0 };

int N, M;
vector<int> g[1010];
int state[1010][1010], visited[1010];
int num_visited;

void dfs(int v) {
	if (visited[v]) return;
	visited[v] = true;
	for (int i = 0; i < g[v].size(); ++i) {
		int u = g[v][i];
		if (not visited[u] and 
			(state[v][u] == Enabled or state[v][u] == Either)) {
			state[v][u] = Enabled;
			state[u][v] = Disabled;
			dfs(u);
		}
	}
}

void dfs_rev(int v) {
	if (visited[v]) return;
	visited[v] = true;
	++num_visited;
	for (int i = 0; i < g[v].size(); ++i) {
		int u = g[v][i];
		if (not visited[u] and 
			(state[v][u] == Disabled or state[v][u] == Either)) {
			state[v][u] = Disabled;
			state[u][v] = Enabled;
			dfs_rev(u);
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	while (cin >> N >> M) {
		if (N == 0 and M == 0) break;
		for (int i = 0; i < N; ++i) g[i].clear();
		for (int i = 0; i < M; ++i) {
			int A, B; cin >> A >> B; --A, --B;
			g[A].push_back(B);
			g[B].push_back(A);
		}
		memset(state, 0, sizeof state);
		memset(visited, false, sizeof visited);
		num_visited = 0;
		dfs(0);

		memset(visited, false, sizeof visited);
		num_visited = 0;
		dfs_rev(0);

		cout << (num_visited == N ? 'S' : 'N') << endl;
	}
}