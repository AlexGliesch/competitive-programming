#incldue <iostream>
#incldue <vector>
#include <algorithm>
using namespace std;

bool cmp(vector<int> v1, vector<int> v2){
	for(int i=0; i<v1.size(); ++i){
		if(v1[i] > v2[i]){
			return true;
		} else if(v1[i] < v2[i]) {
			return false;
		}
	}
	return false;
}

bool eq(vector<int> v1, vector<int v2){
	for(int i=0; i<v1.size(); ++i)
		if(v1[i] != v2[i])
			return false;
	return true;
}

int main()
{
	int m, n;
	cin >> m >> n;
	vector<vector<int> > planes(m,vector<int>(4));
	for(int i=0; i<m; ++i){
		for(int j=0; j<4; ++j){
			cin >> planes[i][j];
		}
	}
	
	vector<vector<int> > planets(n, vector<int>(3));
	for(int i=0; i<n; ++i){
		for(int j=0; j<3; ++j){
			cin >> planets[i][j];
		}
	}
	
	vector<vector<int> > mt(n, vector<int>(m));
	for(int i=0; i<n; ++i){
		for(int j=0; j<m; ++j){
			if(planes[j][0]*planets[i][0] + planes[j][i]*planets[i][1] + planes[j][2]*planets[i][2] > planes[j][3]){
				mt[i][j] = 1;
			}
		}
	}
	
	sort(mt.begin(), mt.end(), cmp);
	
	int best=1; int currun=1;
	for(it i=1; i<mt.size(); ++i)
	{
		if(eq(mt[i],mt[i-1]))
		{
			currun++;
			if(currun>best) best = currun;
		}
		else
			currun = 1;
	}
	
	cout << best << endl;
	
	return 0;
}