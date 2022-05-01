#include <vector>
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

int ages[510];
int visited[510];
vector<vector<int> > g;

int mininum_age(int e, int best, int first) {
	if (visited[e]) return best;
	
	if (e != first) {
		best = min(best, ages[e]);
	}
	visited[e] = 1;	
	for (int i = 0; i < g[e].size(); ++i) {
		if (g[e][i] != first) {
			best = min(best, ages[g[e][i]]);
		}
		best = min(best, mininum_age(g[e][i], best, first));
	}
	return best;
}

int main() {
	ios_base::sync_with_stdio(false);
	int N, M, I;
	while (cin >> N >> M >> I) {
		for (int i = 1; i <= N; ++i)cin >> ages[i];
		g.clear(); g.resize(N + 5);

		for (int i = 0; i < M; ++i) {
			int x, y; cin >> x >> y;
			g[y].push_back(x);
		}
		
		for (int i = 0; i < I; ++i) {
			char instruction; cin >> instruction;
			if (instruction == 'T') {
				int a, b; cin >> a >> b;
				swap(g[a], g[b]);
				for (int k = 1; k <= N; ++k) {
					for (int j = 0; j < g[k].size(); ++j) {
						if (g[k][j] == a) g[k][j] = b;
						else if (g[k][j] == b) g[k][j] = a;
					}
				}
			} else if (instruction == 'P') {
				int e; cin >> e;
				memset(visited, 0, sizeof visited);
				if (g[e].size() == 0) {
					cout << "*" <<endl;
				} else {					
					int best = mininum_age(e, (1 << 28), e);
					cout << best << endl;
				}
			}
		}
	}
}
