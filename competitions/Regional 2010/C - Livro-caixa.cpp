#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <map>
#include <queue>
#define OS 16500
#define mp make_pair

using namespace std;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef long long ll;

int N,F;
vi vals;
vi accum;
string ans;
string ca;
int dp[45][35000];
// map<int, bool> dp[45];

/* 
	returns true if its possible to add 'sum' with elements starting from i
*/

int rec(int i, int sum){
	if (i==N){
		if (sum != F) return dp[i][sum+OS]=0;

		for (int j=0;j<N;++j){
			if (ans[j]=='?') continue;
			if (ans[j]=='.') ans[j]=ca[j];
			else if (ans[j]!=ca[j]) ans[j]='?';
		} 
		return dp[i][sum+OS]=1;
	}

	if (dp[i][sum+OS] != -1) {
		if (dp[i][sum+OS]==1){
			for (int j=0;j<i;++j){
				if (ans[j]=='?') continue;
				if (ans[j]=='.') ans[j]=ca[j];
				else if (ans[j]!=ca[j]) ans[j]='?';		
			}
			return 1;
		}
		return 0;
	}

	if (sum<F and sum+accum[i] < F) return dp[i][sum+OS] = 0;
	if (sum>F and sum-accum[i] > F) return dp[i][sum+OS] = 0;

	ca[i]='+';
	bool a= rec(i+1,sum+vals[i]);

	ca[i]='-';
	bool b= rec(i+1,sum-vals[i]);

	if (a or b) dp[i][sum+OS] = 1;
	else dp[i][sum+OS] = 0;
	return dp[i][sum+OS];
}

int main() {
	ios_base::sync_with_stdio(false);	
	while(cin>>N>>F, N or F){
		// for (int i=0;i<45;++i) dp[i].clear();

		vals.clear();vals.resize(N);
		accum.clear(); accum.resize(N);
		ans.clear(); ans.resize(N,'.');
		ca.clear(); ca.resize(N,'.');

		for (int i=0;i<N;++i){
			cin>>vals[i];
		}
		accum[N-1]=vals[N-1];
		for (int i=N-2;i>=0;--i){
			accum[i]=vals[i]+accum[i+1];
		}

		memset(dp, -1, sizeof dp);
		rec(0,0);
		int num_interr=0;
		for (int i=0;i<N;++i){
			if (ans[i]=='.') ++num_interr;
		}
		if (num_interr==N) cout <<"*"<<endl;
		else cout << ans<<endl;
	}	
}