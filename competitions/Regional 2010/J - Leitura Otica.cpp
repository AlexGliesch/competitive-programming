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

int N; 
int main() {
	ios_base::sync_with_stdio(false);
	while(cin>>N,N){		
		for (int i=0;i<N;++i){
			int val[5];
			for (int j=0;j<5;++j) cin>>val[j];
			int numblack=0;
			int firstblack=-1;
			for (int j=0;j<5;++j){
				if (val[j]<=127) {
					++numblack;
					firstblack=j;
				}
			}
			// cout <<"numblack:"<<numblack<<endl;
			if (numblack==1){
				cout << char('A' + firstblack) << endl;
			} else {
				cout <<"*\n";
			}

		}
	}
}