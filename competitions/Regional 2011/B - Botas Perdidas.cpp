#include <iostream>
#include <cstring>

using namespace std;

/* 
 * a vector that for every shoe size (index), is incremented when a right pair
 * is found and decremented when a left pair is found. when it is negative and
 * incremented, or when it is positive and decremented, add 1 to the final 
 * answer.
 * */

int main(){
	int N, v[100]; 
	while (cin >> N) {
		int ans = 0;
		memset(v, 0, sizeof(v));
		for (int i = 0; i < N; ++i) {
			int m; char L;
			cin >> m >> L;
			if (L == 'D') {
				if (v[m] < 0) ++ans;					
				++v[m];
			} else {
				if (v[m] > 0) ++ans;
				--v[m];
			}
		}
		cout << ans << endl;
	}
}