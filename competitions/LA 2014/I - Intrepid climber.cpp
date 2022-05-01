#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/* 
 * run a dfs on the tree. the dfs of a branch  returns two things: if a friend 
 * was found on that branch, and the total weight needed to visit all friends
 * on that branch.
 * 
 * if a node is already a friend and has no neighbours, then the total weight 
 * is 0, and a friend was found.
 * 
 * if a node u has neighbours, run dfs(v) recursively for all neighbour v. 
 * if dfs(v) finds a friend, then add the weight w(v, u) to the answer of 
 * dfs(u). if no friends are found in a branch, then that branch contributes 
 * nothing.
 * 
 * one detail: the idea is that the climber should always stop at the
 * lowest possible landmark (because you dont have to climb back up). so, we
 * take the total depth (=dfs(1)) and subtract the largest depth for any of the 
 * friends, and that is the answer.
 * */

int N, F, max_depth;
vector<vector<pair<int, int>>> g;
vector<int> friends;

int dfs(int v, int& found_friend, int depth) {
	int ans = 0;
	if (friends[v]) {
		max_depth = max(depth, max_depth);
		++found_friend;
	}
	for (const auto& p : g[v]) {
		int found = 0;
		int w = dfs(p.second, found, depth + p.first);
		if (found) {
			found_friend = 1;
			ans += w + p.first;
		}
	}
	return ans;
}

int main() {
	ios_base::sync_with_stdio(false);
	while (cin >> N >> F) {
		g.clear(); g.resize(N);
		friends.clear(); friends.resize(N, 0);
		
		for (int i = 0; i < N - 1; ++i) {
			int A, B, C; cin >> A >> B >> C;
			g[A-1].emplace_back(C, B-1);
		}
		for (int i = 0; i < F; ++i) {
			int Fi; cin >> Fi;
			friends[Fi - 1] = 1;
		}
		max_depth = 0;
		int found = 0;
		int ans = dfs(0, found, 0);
		cout << ans - max_depth << endl;
	}
}