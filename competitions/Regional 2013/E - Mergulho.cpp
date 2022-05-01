#include <iostream>
#include <cstring>

using namespace std;

int foram[10010], chegaram[10010];

int main() {
	int n, r;
	while (cin >> n >> r) {
		memset(chegaram, 0, sizeof chegaram);
		for (int i = 1; i <= r; ++i) {
			int x; cin >> x;
			chegaram[x] = true;
		}
		
		if (n == r) { cout << "*" << endl; continue; }
		
		bool first = 0;
		for (int i = 1; i <= n; ++i) {
			if (not chegaram[i]) {
				cout << i << " ";
			}			
		}
		cout <<endl;		
	}
}
