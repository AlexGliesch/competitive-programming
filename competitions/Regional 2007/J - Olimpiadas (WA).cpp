#include <queue>
#include <vector>
#include <ciso646>
#include <algorithm>
#include <iostream>
#include <limits>

using namespace std;

/* 
 * the idea: run edmonds-karp max flow, and store the size and max flow of 
 * all augmenting paths found. then simulate the persons arriving at Beijing
 * at every iteration since the start:
 * 
 * day = 0, total_flow = 0
 * while (total_flow < A) {
 *	for (p in augmenting_paths):
 *		if (--p.path_length <= 0) 
 *			total_flow += p.flow
 *		++day
 * }
 * 
 * then we print "day".
 * 
 * well, this should work, and in fact it does work for 225 out of the 226
 * tests, and one of them the algorithm outputs 30 where the 'correct' answer
 * should be 29. i don't know if its me who is wrong or the given solutions
 * which are wrong; and i've no idea what could be wrong and how to fix it.
 * 
 * on the bright side, no teams at the contest even attempted to solve this 
 * problem, so i think getting over 99.5% of the test cases is already a 
 * success.
 * 
 * */

struct Edge { 
	Edge(int from, int to, int cap, int flow) : 
		from(from), to(to), cap(cap), flow(flow) { }
	int from, to, cap, flow; 
};

vector<Edge> edge;
vector<int> pred;
int N, M, A;
int n, s, t;
vector<vector<int> > g;
vector<pair<int, int> > paths; /* first: flow, second: path-len */

void add_edge(int u, int v, int c) {
	g[u].push_back(edge.size());
	edge.push_back(Edge(u, v, c, 0));
	g[v].push_back(edge.size());
	edge.push_back(Edge(v, u, 0, 0));
}

bool bfs() {
	pred.assign(n, -1);
	queue<int> q; q.push(s);
	pred[s] = -2; /* some unique value */
	while (q.size()) {
		int v = q.front(); q.pop();
		for (int i = 0; i < g[v].size(); ++i) {
			int e = g[v][i];
			if (edge[e].cap - edge[e].flow <= 0) continue;
			int u = edge[e].to;
			if (pred[u] == -1) {
				pred[u] = e;
				q.push(u);
			}
		}
	}
	return pred[t] != -1;
}

int edmonds_karp_max_flow() {
	int total_flow = 0;
	while (bfs()) {
		int f = numeric_limits<int>::max();
		int path_len = 0;
		for (int e = pred[t]; e != pred[s]; e = pred[edge[e].from]) {
			f = min(f, edge[e].cap - edge[e].flow);
			++path_len;
		}
		paths.push_back(make_pair(f, path_len));		
		if (f == 0) continue;
		for (int e = pred[t]; e != pred[s]; e = pred[edge[e].from]) {
			edge[e].flow += f;
			edge[e ^ 1].flow -= f;
		}
		total_flow += f;
	}
	return total_flow;
}

int main() {
	ios_base::sync_with_stdio(false);	
	int k = 1;
	while (cin >> N >> M >> A) {		
		if (N == 0 and M == 0 and A == 0) break;
		n = N, s = 0, t = N - 1;
		g.clear(); g.resize(n);
		edge.clear();
		paths.clear();

		for (int i = 0; i < M; ++i) {
			int O, D, S; cin >> O >> D >> S; --O, --D;
			add_edge(O, D, S); 			
		}

		edmonds_karp_max_flow();

		//for (int i = 0; i < paths.size(); ++i) {
		//	cout << "Path " << i + 1 << ": " << paths[i].first << " flow, " 
		//		<< paths[i].second << " len" << endl;
		//}

		int ans = 0, tf = 0;
		while (tf < A) {
			//cout << "Day " << ans+1 << ": " << endl;
			for (int i = 0; i < paths.size(); ++i) {
				paths[i].second = max(paths[i].second - 1, 0);
				if (paths[i].second == 0) {					
					tf += paths[i].first;
					//cout << "add " << paths[i].first << " from path " << i + 1
					//   << ", total flow: " << tf << endl;
				}				
			}
			++ans;
		}		
		cout << ans << endl;
	}
}