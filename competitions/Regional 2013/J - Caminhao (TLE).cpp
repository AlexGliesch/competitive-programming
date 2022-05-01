#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;
typedef pair<int, int> ii;

vector<vector<ii> > g;
int n, m, S;
int distances[20010][20010];
vector<bool> computed;

void bfs(int s){
	priority_queue<ii> pq;
	vector<int> pred(n, -1);
	distances[s][s] = (1 << 28);
	pq.push(ii(1 << 28, s));
	while (pq.size()) {
		int cost = pq.top().first, u = pq.top().second; pq.pop();
		if (distances[s][u] != cost) continue;
		for (int i = 0; i < g[u].size(); ++i) {
			int v = g[u][i].second, w = min(g[u][i].first, cost);
			if (distances[s][v] < w) {
				distances[s][v] = w;
				pred[v] = u;
				pq.push(ii(w, v));
			}
		}
	}
	
	for (int i = 0; i < n; ++i) {
		int cur = i;
		while (cur != -1) {
			distances[cur][i] = distances[s][i];
			cur = pred[cur];
		}
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	while (cin >> n >> m >> S) {
		g.clear(); g.resize(n);
		memset(distances, -1, sizeof distances);
		for (int i = 0; i < m; ++i) {
			int a, b, p; cin >> a >> b >> p; --a, --b;
			g[a].push_back(ii(p, b));
			g[b].push_back(ii(p, a));
		}
		
		for (int i = 0; i < S; ++i) {
			int a, b; cin >> a >> b; --a, --b;
			if (distances[a][b] != -1) {
				cout << distances[a][b] << endl;
			} else if (distances[a][b] != -1) {
				cout << distances[b][a] << endl;
			} else {
				bfs(a);
				cout << distances[a][b] << endl;
			}			
		}
	}
}
