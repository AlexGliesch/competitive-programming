#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <map>
#include <queue>
#include <string>
#define mp make_pair

using namespace std;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef long long ll;

/* strategy: 

always put in the first place where you wont lose

*/

int N; 
string v;

enum{won, lost, keep};

int put(){
	vi posx;
	posx.push_back(-3);
	for (int i=0;i<N;++i){
		if (v[i]=='X') posx.push_back(i);
		if (i >=2 and v[i] != 'X' and v[i-1] == 'X' and v[i-2]=='X') {
			return won;		
		}
		if (i <= N-1-2 and v[i]!='X' and v[i+1]=='X' and v[i+2]=='X'){
			return won;
		}
		if (i >= 1 and i <= N-2 and v[i] != 'X' and v[i+1]=='X' 
			and v[i-1]=='X'){
			return won;
		}
	}
	posx.push_back(N+2);

	int ans=lost;
	for (int i=1; i < posx.size();++i){
		if (posx[i] - posx[i-1] >= 5) {
			ans=keep;
			cout << "put X in " << (posx[i]+posx[i-1])/2 << endl;
			v[(posx[i]+posx[i-1])/2]='X';			
			break;
		}
	}
	return ans;
}

int main() {
	ios_base::sync_with_stdio(false);
	while(cin>>N,N){
		cin>>v;

		int i=2;
		while(true){
			int ans=put();
			++i;
			if (ans==lost){
				if (i % 2 == 0) cout <<"S"<<endl;
				else cout <<"N"<<endl;
				break;
			} else if (ans==won){
				if (i % 2 == 0) cout <<"N"<<endl;
				else cout <<"S"<<endl;
				break;
			}
		}		
	}	
}