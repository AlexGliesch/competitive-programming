#include <iostream>
#include <algorithm>
#include <queue>
#include <cstring>

using namespace std;

/* 
 * something they don't make very clear from the problem description:
 * the EDP is the SUM of products time*energy for every task, plus the SUM 
 * of E*D for every change of frequency required. it is not the product of the
 * sum of times and the sum of energies!
 * 
 * having this realization, we know that the cost of switching from a frequency
 * to another in solving a task does not depend on the current energy/time
 * spent so far. 
 * 
 * we can see the problem as a graph: each task+frequency is a node. every
 * task node has an edge to all other task nodes for the following task; these
 * edges have weight E*D + E_(i,j)*D(i,j), except for the edge with the same
 * frequency, which has weight E_(i,j)*D(i,j). thus, we can run dijkstra on this
 * graph until we reach the last task. by dijkstra's optimality, the first node
 * of the last task reached will always be the cheapest way to reach the
 * last task.
 * 
 * ps: the i/o for this problem is VERY large, so you should use
 * std::sync_with_stdio(false) always, otherwise you would get TLE!
 * 
 */

int f, p, e, d, ED[5010][30], ed, dist[5010][30];

struct State {
	State(int p, int f, int e) : prog(p), freq(f), edp(e) {}
	int edp, prog, freq;
	bool operator<(const State& s) const { return edp > s.edp; }
};

int dijkstra(){
	priority_queue<State> pq;
	memset(dist, -1, sizeof(dist));
	State init(0, 1, 0);;
	dist[0][1] = 0;
	pq.push(init);

	while (pq.size()) {		
		State s = pq.top(); pq.pop();
		if (dist[s.prog][s.freq] != s.edp) continue;
		if (s.prog == p) return s.edp;

		for (int j = 1; j <= f; ++j) {
			int np = s.prog + 1;
			int cd = s.edp + ED[np][j];			

			if (j != s.freq) cd += ed;

			if (dist[np][j] == -1 or dist[np][j] > cd) {				
				dist[np][j] = cd;
				State ns(np, j, cd);
				pq.push(ns);
			}
		}

	}
	return -1;
}

int main() {
	ios_base::sync_with_stdio(false);
	while (cin >> f >> p >> e >> d) {
		if (f == 0 and p == 0 and e == 0 and d == 0) break;
		ed = e*d;		
		for (int i = 1; i <= p; ++i) {
			for (int j = 1; j <= f; ++j) {
				int x, y; cin >> x >> y;
				ED[i][j] = x*y;
			}
		}
		cout << dijkstra() << endl;
	}
}
