#include <vector>
#include <iostream>
#include <unordered_set>
#include <algorithm>

using namespace std;

/* 
 * the answer is the number of different GCD of all possible paths on the graph.
 * a GCD of a path is the GCD of the values of all the nodes in that path.
 * 
 * the idea is to run multiple dfs's, one starting from every node, in the
 * following way: 
 * 
 * dfs(u, current_gcd):
 *     answer = answer U { current_gcd } // answer is a set
 *     for v in neighbours(u):
 *	        dfs(v, GCD(values[v], current_gcd) 
 *	        
 * of course, this will run literally forever, so we must keep a DP vector 
 * dp[u][current_gcd] that tells whether a certain dfs has already been done. 
 * if a dfs has already been done, we can promptly return. 
 *
 * because 'u' can be up to 10^4 and 'current_gcd' up to 10^5, we can't use a 
 * plain C array, so we must use sets/maps for the DP.
 * 
 * */

int I, S;
int values[10010];
vector<vector<int>> g;
vector<unordered_set<int>> visited;
unordered_set<int> ans;

void dfs(int u, int gcd) {
	if (visited[u].find(gcd) != visited[u].end())
		return;
	visited[u].insert(gcd);
	ans.insert(gcd);
	for (auto v : g[u]) 
		dfs(v, __gcd(values[v], gcd));
}

int main() {
	ios_base::sync_with_stdio(false);
	while (cin >> I >> S) {
		ans.clear();
		visited.clear(); visited.resize(I);
		g.clear(); g.resize(I);
		for (int i = 0; i < I; ++i) 
			cin >> values[i];		
		for (int i = 0; i < S; ++i) {
			int to, from; cin >> to >> from;
			g[to-1].push_back(from-1);
			g[from - 1].push_back(to - 1);
		}
		for (int i = 0; i < I; ++i) {			
			dfs(i, values[i]);
		}
		cout << ans.size() << endl;
	}
}