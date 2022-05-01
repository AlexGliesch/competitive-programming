#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>

using namespace std;
typedef pair<int, int> ii;

/*
* it is a problem of finding "articulation points" on a graph. in this
* particular problem, since the edges are directed, we cannot run tarjan's
* O(n+m) algorithm, so we have to use the naive solution.
*
* first, start a
* dfs from the capital and see how many nodes were visited. then, iterate over
* all the edges and try to disable one by one and run a dfs then, counting the
* number of visited nodes. if, by disabling any of the edges, the number of
* visited nodes from the capital is less than before, then that edge is an
* articulation point, and therefore is critical.
*
* don't forget to sort the critical edges by the order in which they are input.
*
* */

int n, m, num_visited;
vector<vector<int> > g;
map<ii, int> edge_num;
vector<bool> visited;

void dfs(int v, int disable_from, int disable_to) {
	if (visited[v]) return;
	visited[v] = true;
	++num_visited;
	for (int i = 0; i < g[v].size(); ++i) {
		if (v == disable_from and i == disable_to) continue;
		if (not visited[g[v][i]]) {
			dfs(g[v][i], disable_from, disable_to);
		}
	}
}

/* sort list of edges by the order in which they were added */
bool compare(const ii& a, const ii& b) {
	return edge_num[a] < edge_num[b];
}

int main() {
	ios_base::sync_with_stdio(false);
	while (cin >> n >> m, not(n == 0 and m == 0)) {
		g.clear(); g.resize(n + 1);
		map<string, int> strtoi;
		map<int, string> itostr;
		for (int i = 0; i < n; ++i) {
			string s; cin >> s;
			strtoi[s] = i;
			itostr[i] = s;
		}

		edge_num.clear();
		for (int i = 0; i < m; ++i) {
			string u, v; cin >> u >> v;;
			g[strtoi[v]].push_back(strtoi[u]);
			edge_num[ii(strtoi[u], strtoi[v])] = i;
		}

		num_visited = 0;
		visited.assign(n, false);
		dfs(0, -1, -1);

		int first_visited = num_visited;
		vector<pair<int, int> > critical_edges;

		for (int v = 0; v < n; ++v) {
			for (int j = 0; j < g[v].size(); ++j) {
				num_visited = 0;
				visited.assign(n, false);
				dfs(0, v, j);

				if (num_visited < first_visited)
					critical_edges.push_back(ii(g[v][j], v));
			}
		}
		sort(critical_edges.begin(), critical_edges.end(), compare);

		if (critical_edges.size() == 0) {
			cout << "Nenhuma" << endl;
		} else {
			for (int i = 0; i < critical_edges.size(); ++i) {
				cout << itostr[critical_edges[i].first] << " "
					<< itostr[critical_edges[i].second] << endl;
			}
		}
		cout << endl;
	}
}