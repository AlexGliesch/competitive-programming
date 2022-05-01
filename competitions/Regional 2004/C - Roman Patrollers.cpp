#include <iostream>
#include <algorithm>
#include <vector>

typedef std::pair<int, int> ii;
using namespace std;

/* 
 * you need to do a graph traversal in the order that is specified by the 
 * description: always visit first the neighbour with the largest ICI 
 * (idleness).
 * 
 * the problem is not tricky, however, it has a few details. say, for instance,
 * a patroller is in cycle N and going through an edge with cost 5. it will
 * only arrive at the destination at cycle N+5; by then, all the nodes in
 * the graph will have increased their ICI by 5. you then set the destination's
 * ICI to be 0, and add all other ICI's to get the current empire idleness.
*/

int C, R, N, S;
vector<vector<ii> > g;

int main() {
	while (cin >> C >> R >> N >> S, C and R and N and S) {
		g.clear(); g.resize(C + 1);
		for (int i = 0; i < R; ++i) {
			int x, y, d; cin >> x >> y >> d;
			g[x].push_back(ii(y, d));
			g[y].push_back(ii(x, d));
		}

		vector<int> ici(C + 1, 0);
		int cur = S, ei = 0;

		for (int i = 0; i < N; ++i) {
			int max_n = 0; /* most idle neighbour index */
			for (int j = 1; j < g[cur].size(); ++j) {
				ii& u = g[cur][j], &largest = g[cur][max_n];
				if (ici[u.first] > ici[largest.first] or
					ici[u.first] == ici[largest.first] and
					u.first < largest.first) {
					max_n = j;
				}
			}

			int D = g[cur][max_n].second, next = g[cur][max_n].first;
			int iei = 0, partial_iei = 0;

			if (D > 1) {
				for (int j = 1; j <= C; ++j) partial_iei += ici[j];
			}

			for (int d = 1; d <= D - 1; ++d) {
				iei += (partial_iei + C*d);				
				if (++i >= N) 
					goto leave;				
			}

			/* last iteratio n*/
			ici[next] = 0;
			for (int j = 1; j <= C; ++j) {
				if (j != next) {
					ici[j] += D;
					iei += ici[j];
				}
			}
		leave:
			ei += iei;
			cur = next;
		}
		cout << ei << endl;
	}
}