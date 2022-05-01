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

char N; string D;

struct is_N{
	bool operator()(char c) const{
		return c == N;
	}
};

int main() {
	ios_base::sync_with_stdio(false);
	while(cin>>N>>D){
		if (N=='0' and D=="0") break;
		D.erase(remove_if(D.begin(),D.end(), is_N()), D.end());
		while(D.size() > 1 and D[0]=='0') D.erase(D.begin());
		if (D.empty()) D="0";
		cout << D <<endl;
	}
	
}