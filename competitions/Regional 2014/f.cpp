#include <iostream>
#include <vector>
using namespace std;

#define MOD 10000
typedef vector<vector<int> > mat;

void mul(mat a, mat b, mat& resp)
{
	for(int i=0;i<resp.size();++i)
		for(int j=0;j<resp[i].size();++j)
		{
			resp[i][j]=0;
			for(int k=0;k<a[i].size();++k)
				resp[i][j] = (resp[i][j] + a[i][k]*b[k][j])%MOD;
		}
}

mat pot(mat b,int p)
{
	if(p==1) return b;
	mat m = pot(b,p/2);
	mul(m,m,m);
	if(p%2==1) mul(m,b,m);
	return m;
}

int main()
{
	int n,l,s,t;
	cin >> n >> l >> s >> t;
	
	if(l==0) {cout << (s==t?1:0) << endl; return 0;}
	
	mat g(n,vector<int>(n,0));
	for(int i=0;i<n;++i)
	{
		int a,b,c,d;
		cin >> a >> b >> c >> d;
		g[i][a-1]++;
		g[i][b-1]++;
		g[i][c-1]++;
		g[i][d-1]++;
	}
	
	mat resp = pot(g,l);
	cout << resp[s-1][t-1] << endl;
}