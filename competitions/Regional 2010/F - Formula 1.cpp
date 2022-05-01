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

int g,p;
vector<vi> order; // order[i][1]==2 if pilot #1 was 2nd in GP i
vector<vi> sys;
vector<vi> pts_sys;

void get_pts_sys(int i){
	for (int gp=1;gp<=g;++gp){
		for (int pl=1;pl<=p;++pl){
			pts_sys[i][pl] += sys[i][order[gp][pl]];
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	while(cin>>g>>p, g or p){
		order.clear();
		order.resize(g+5, vi(p+5,0));
		for (int i=1;i<=g;++i){
			for (int j=1;j<=p;++j){
				cin>>order[i][j];
			}
		}

		int s; cin>>s;
		sys.clear();
		sys.resize(s+5,vi(p+5,0));
		pts_sys = sys;
		for (int i=1;i<=s;++i){
			int k; cin>>k;
			for (int j=1;j<=k;++j){
				cin>>sys[i][j];
			}
		}

		for (int i=1;i<=s;++i){
			get_pts_sys(i);
			int maxpt=-1;
			for (int pl=1;pl<=p;++pl){
				maxpt=max(maxpt,pts_sys[i][pl]);
			}
			bool first=true;
			for (int pl=1;pl<=p;++pl){
				if (pts_sys[i][pl]==maxpt){
					if (!first) cout<<" ";
					first=false;
					cout << pl;
				}
			}
			cout << endl;
		}
	}
}