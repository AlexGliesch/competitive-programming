#include <stack>
#include <vector>
#include <iostream>
#include <ciso646>
#include <algorithm>

using namespace std;

/* 
 * greedy recursive solution: you will always unstack either always from the
 * left or always from the right. so the solution is the minimum between
 * unstacking from the left and from the right.
 * 
 * try unstacking all boxes from the pile where 1 is. to unstack a box, 
 * while it is not free, unstack a box from the neighbour pile (either right
 * or left, depending on which iteration you are running), by calling the 
 * recursive unstacking procedure.
 * */

int N, P;
vector<stack<int> > g;

bool is_top_free(int p) {
	if (p <= 0 or p >= P - 1) return true;
	return g[p].size() == 0 or
		g[p + 1].size() < g[p].size() or
		g[p - 1].size() < g[p].size();
}

int unstack(int p, int o) {
	//cout << "unstack(" << p << ", " << o << ")" << endl;
	if (g[p].size() == 0) return 0;
	int ans = 0;
	while (not is_top_free(p)) {
		ans += unstack(p + o, o);		
	}
	g[p].pop();
	return ans + 1;
}

int main() {
	while (cin >> N >> P) {
		if (N == 0 and P == 0) break;
		g.clear(); g.resize(P);

		int p1 = -1;
		for (int i = 0; i < P; ++i) {
			int Q; cin >> Q;
			for (int j = 0; j < Q; ++j) {
				int k; cin >> k;
				g[i].push(k);
				if (k == 1) p1 = i;
			}
		}

		int ans_l = 0, ans_r = 0;
		vector<stack<int> > g2 = g;
		while (g[p1].size() > 0 and g[p1].top() != 1)
			ans_l += unstack(p1, -1);
		ans_l += unstack(p1, -1);

		g = g2;
		while (g[p1].size() > 0 and g[p1].top() != 1)
			ans_r += unstack(p1, 1);		
		ans_r += unstack(p1, 1);

		cout << max(0, min(ans_r, ans_l) - 1) << endl;
	}

}