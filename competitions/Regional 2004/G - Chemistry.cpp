#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <iostream>
#include <limits>

using namespace std;

/* 
 * You can view the reactions as a DAG: if T1 depends on A and B, there's an
 * edge from T1->A and an edge from T1->B. 
 * Generate the graph (using map and string is good enough), run a dfs 
 * starting from the last element, using the recurrence:
 * 
 * dfs(v):
 * 	if (v is leaf) return 1
 * 	if (v has only 1 neighbour, n1) return dfs(n1)
 * 	else return min(max(dfs(n1), dfs(n2) + 1), max(dfs(n1 + 1), dfs(n2)));
 * 
 * (note that a node will never have more than 2 incoming edges!)
 * Why min(...)? It is the minimum of first making reactor 1 and then 2, or 
 * first making 2 and then 1.
 * 
 * Use a dp vector to store the dfs solution for a given node.
*/

string i1, i2, i3, buf;
int n;
map<string, vector<string> > g;
map<string, int> dp;

int dfs(const string& v){
	map<string, int>::iterator it = dp.find(v);
	if (it != dp.end()) 
		return it->second;	
	
	int ans = numeric_limits<int>::max();
	if (g[v].size() == 1) {
		ans = dfs(g[v][0]);
	} else {
		// Assuming g[v].size() <= 2!
		int ans1 = dfs(g[v][0]), ans2 = dfs(g[v][1]);
		ans = min(max(ans1, ans2 + 1), max(ans1 + 1, ans2));
	}
	
	return dp[v] = ans;
}

int main() {
	while (cin>>n, n) {
		g.clear(); dp.clear();
		string p; // Last reactor
		for (int i = 0; i < n; ++i) {
			cin >> i1 >> buf >> i2 >> buf >> i3;
			g[i3].clear(); // Create g[i3]
			
			map<string, vector<string> >::iterator f1 = g.find(i1), 
				f2 = g.find(i2);
			if (f1 != g.end()) { g[i3].push_back(i1); }
			if (f2 != g.end()) { g[i3].push_back(i2); }
			if (f1 == g.end() and f2 == g.end())
				dp[i3] = 1;
			if (i == n-1) p = i3;
		}		
		
		int ans = dfs(p);
		cout << p << " requires " << ans << " containers" <<endl;
	}
}