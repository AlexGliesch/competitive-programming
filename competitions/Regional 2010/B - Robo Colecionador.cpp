#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <map>
#include <string>
#include <queue>
#define mp make_pair

using namespace std;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef long long ll;

int N,M,S;
vector<string> g;
string instr;

bool invalid(int x, int y){
	return x<0 or x>=M or y<0 or y>=N or g[y][x]=='#';
}

int main() {
	ios_base::sync_with_stdio(false);
	while(cin>>N>>M>>S, N or M or S){
		g.clear();g.resize(N);
		for (int i=0;i<N;++i) cin >> g[i];
		cin>>instr;

		char ori;
		int x,y;

		for (int i=0;i<N;++i){
			for (int j=0;j<M;++j){
				if (g[i][j]>='A' and g[i][j] <= 'Z'){
					ori=g[i][j];
					x=j; 
					y=i;
					break;
				}
			}
		}

		int ans=0;
		for (int i=0;i<S;++i){
			if (instr[i]=='D'){
				if (ori=='N') ori='L';
				else if (ori=='L') ori='S';
				else if (ori=='S') ori='O';
				else if (ori=='O') ori='N';
			} else if (instr[i]=='E'){
				if (ori=='N') ori='O';
				else if (ori=='O') ori='S';
				else if (ori=='S') ori='L';
				else if (ori=='L') ori='N';
			} else if (instr[i]=='F'){
				int dx,dy;
				if (ori=='N'){
					dx=0,dy=-1;
				} else if (ori=='L'){
					dx=1,dy=0;
				} else if (ori=='S'){
					dx=0,dy=1;
				}else if (ori=='O'){
					dx=-1,dy=0;
				}
				if (invalid(x+dx,y+dy)) continue;
				x += dx, y+=dy;
				if (g[y][x]=='*'){
					++ans;
					g[y][x]='.';
				}
			}
		}
		cout <<ans<<endl;
	}
}