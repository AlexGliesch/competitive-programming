#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <map>
#include <queue>
#define mp make_pair

using namespace std;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef long long ll;

vector<vi> g, grev;
vector<bool> visited;
int num_visited;
int n,m;

void dfs(int v, vector<vi>& g){
	if (visited[v]) return;
	visited[v]=true;
	++num_visited;
	for (int i=0;i<g[v].size();++i){
		if (not visited[g[v][i]])
			dfs(g[v][i], g);
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	// cout<<"0\n";
	while(cin>>n>>m){
		// cout <<"0.2\n";
		if (n==0 and m==0) break;
		// cout <<"1\n";
		g.clear(); g.resize(n+1);
		// cout <<"2\n";

		grev.clear(); grev.resize(n+1);
		// cout<<"start\n";
		for (int i=0;i<m;++i){
			// cout<<"i"<<i<<"\n";
			int v,w,p; cin>>v>>w>>p;
			g[v].push_back(w);
			grev[w].push_back(v);
			if (p==2){
				g[w].push_back(v);
				grev[v].push_back(w);
			}
		}	
		// cout<<"red\n";

		visited.assign(n+1, false);
		num_visited=0;
		dfs(1, g);
		int nv_normal=num_visited;

		// cout<<"dfs1 done\n";
		visited.assign(n+1, false);
		num_visited=0;
		dfs(1, grev);
		int nv_rev=num_visited;
		// cout<<"dfs2 done\n";


		if (nv_normal == n and nv_rev == n){
			cout<<1<<endl;
		} else {
			cout<<0<<endl;
		}
	}
}