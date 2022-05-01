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

vector<vector<ii> > g;

int N,M,C,K;
void add_edge(int u, int v, int p){ // from u to v
	if (u < C){
		if (v != u+1) return;
	}
	g[u].push_back(mp(v,p));
}

int dijkstra(){
	vi dist(N,-1);
	priority_queue<ii> pq;
	dist[K]=0;
	pq.push(mp(0,K));
	while(pq.size()){
		int w=-pq.top().first;
		int v=pq.top().second;
		pq.pop();
		if (dist[v]!=w) continue;
		if (v==C-1){
			return w;
		}
		for (int i=0;i<g[v].size();++i){
			int u=g[v][i].first;
			int cd=w+g[v][i].second;
			if (dist[u]==-1 or dist[u]>cd){
				dist[u]=cd;
				pq.push(mp(-cd,u));
			}
		}
	}
	return -1;
}

int main() {
	ios_base::sync_with_stdio(false);
	while(cin>>N>>M>>C>>K, N or M or C or K){
		g.clear();g.resize(N);
		for (int i=0;i<M;++i){
			int u,v,p; cin>>u>>v>>p;
			add_edge(u,v,p);
			add_edge(v,u,p);
		}
		cout << dijkstra() << endl;
	}
}