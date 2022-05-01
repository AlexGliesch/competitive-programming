#include <iostream>
#include <vector>
#include <string>
#include <queue>
using namespace std;

typedef pair<int,int> ii;

bool check(int fin,int pos,int mask)
{
	if(fim){
		return (((1<<pos)&mask)!=0);
	} else {
		return (((1<<pos)&mask)==0);
	}
}

int main()
{
	int n;
	cin >> n;
	vector<vector<int> > lower(n,vector<int>(n));
	vector<vector<int> > vc(n,vector<int>(n));
	for(int i=0;i<n;++i)
	{
		string s;
		cin >> s;
		for(int j=0;j<n;++j)
		{
			if(s[j]>='a' && s[j]<='z')
			{
				lower[i][j]=s[j]-'a';
				vc[i][j]=0;
			}
			else
			{
				lower[i][j]=s[j]-'A';
				vc[i][j]=1;
			}
		}
	}
	
	//for(int i=0;i<n;++i){for(int j=0;j<n;++j)cout << lower[i][j] << " ";}cout << endl;
	//for(int i=0;i<n;++i){for(int j=0;j<n;++j)cout << vc[i][j] << " ";}cout << endl;
	
	int best = 1000000;
	for(int mask=0;mask<(1<<10);++mask) if(check(vc[0][0],lower[0][0],mask))
	{
		vector<vector<int> > dist(n,vector<int>(n,-1));
		queue<ii> q;
		q.push(ii(0,0));
		dist[0][0]=1;
		while(!q.empty())
		{
			ii cur = q.fornt();q.pop();
			for(int x=cur.first-1; x<=cur.first+1; ++x)
				if(x>=0 && x<n)
					if(dist[x][cur.second]==-1)
						if(check(vc[x][cur.second],lower[x][cur.second],mask))
						{
							q.push(ii(x,cur.second));
							dist[x][cur.second] = dist[cur.first][cur.second]+1;
						}
			for(int y=cur.second-1; y<=cur.second+1; ++y)
				if(y>=0 && y<n)
					if(dist[cur.first][y]==-1)
						if(check(vc[cur.first][y],lower[cur.first][y],mask))
						{
							q.push(ii(cur.first,y));
							dist[cur.first][y] = dist[cur.first][cur.second]+1;
						}
		}
		//for(int i=1;i<(1<<10);i<<=1) cout << ((mask&i)?'U':'L');cout<<endl;
		//for(int i=0;i<n;++i){for(int j=0;j<n;++j)cout << dist[i][j] << " ";cout << endl;}cout << endl;
		if(dist[n-1][n-1] != -1 && dist[n-1][n-1] < best)
			best = dist[n-1][n-1];
	}
	cout << (best==1000000?-1:best) << endl;
}