#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <map>
#include <queue>
#define MAXN 100010
#define mp make_pair

using namespace std;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef long long ll;

map<string, int> keytoint;
int maxkey;

void initkeytoint(){
	keytoint["C"]=0;
	keytoint["B#"]=0;
	
	keytoint["Db"]=1;
	keytoint["C#"]=1;

	keytoint["D"]=2;

	keytoint["Eb"]=3;
	keytoint["D#"]=3;

	keytoint["E"]=4;
	keytoint["Fb"]=4;

	keytoint["F"]=5;
	keytoint["E#"]=5;

	keytoint["Gb"]=6;
	keytoint["F#"]=6;

	keytoint["G"]=7;

	keytoint["Ab"]=8;
	keytoint["G#"]=8;

	keytoint["A"]=9;

	keytoint["Bb"]=10;
	keytoint["A#"]=10;

	keytoint["B"]=11;
	keytoint["Cb"]=11;

	maxkey=11;

	// ...

}

int m,t;
vi musica, trecho;
vi t2;

int b[MAXN]; /* back table for kmp. */

void kmp_preprocess(const vi& p /* pattern */) {
	int i = 0, j = -1, m = p.size();
	b[0] = -1;
	while (i < m) {
		while (j >= 0 and p[i] != p[j]) j = b[j];
		++i, ++j;
		b[i] = j;
	}
}

/* 
 * this kmp_search will simply count the number of occurences of p in s. 
 * */
int kmp_search(const vi& s, const vi& p) {
	int i = 0, j = 0, n = s.size(), m = p.size(), ans = 0;
	while (i < n) {
		while (j >= 0 and s[i] != p[j]) j = b[j];
		++i, ++j;
		if (j == m) {
			j = b[j];
			++ans;
		}
	}
	return ans;
}

int main() {
	ios_base::sync_with_stdio(false);
	initkeytoint();

	while(cin>>m>>t, m or t){
		musica.clear(); musica.resize(m);
		trecho.clear(); trecho.resize(t);
		for (int i=0;i<m;++i){
			string s; cin>> s;
			musica[i]=keytoint[s];
		}

		for (int i=0;i<t;++i){
			string s; cin>> s;
			trecho[i]=keytoint[s];
		}

		bool plagio=false;
		for (int i=0;i<=maxkey;++i){
			// all displacements
			t2=trecho;
			for (int j=0;j<t;++j){
				t2[j] = (trecho[j]+i) % (maxkey+1);
			}

			kmp_preprocess(t2);
			if (kmp_search(musica,t2)){
				plagio=true;
				break;
			}
		}

		if (plagio){
			cout <<"S\n";
		} else {
			cout<<"N\n";
		}
	}	
}