#include <iostream>
#include <vector>
#include <cstdio>
#include <cmath>
using namespace std;

typedef pair<double,double> pt;

vector<vector<double> > memo;
vector<pt> inp;
int n;

double INF = 100000000000.0;

double min(double a,double b)
{
	if(a<b) return a;else return b;
}

double f(int x,int y)
{
	if(((y-x+n)%n)%2==0) return INF;
	if(((y-x+n)%n)==1) return 0;
	if(memo[x][y] > 0) return memo[x][y];
	double best = INF;
	for(int i=(x+1)%n; i!=(y-1+n)%n && i!=y; i=(i+2)%n)
		for(int j=(i+1)%n; j!=y && j!=(y+1)%n; j=(j+2)%n)
			best = min(best,f(x,i)+f(i,j)+f(j,y));
	double dx=inp[x].first-inp[y].first, dy=inp[x].second-inp[y].second;
	best+=sqrt((dx*dx)+(dy*dy));
	memo[x][y]=best;
	return best;
}

int main()
{
	cin >> n;
	n*=2;
	inp.resize(n);
	for(int i=0;i<n;++i)
		cin >> inp[i].first >> inp[i].second;
	
	memo.resize(n,vector<double>(n,-1));
	double best = INF;
	for(int i=0;i<n;++i)
		best = min(best,f(i,(i-3+n)%n));
	
	printf("%.4lf\n",best);
}