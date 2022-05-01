#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int main() {
	int A, D; 
	while (cin >> A >> D, A and D) {
		vector<int> a(A), d(D);
		for (int i = 0; i < A; ++i) cin >> a[i];
		for (int i = 0; i < D; ++i) cin >> d[i];
		
		int lastO = (1<<28), lastO2 = (1<<28);
		for (int i = 0; i < D; ++i) {
			if (d[i] <= lastO) {
				lastO2 = lastO;
				lastO = d[i];
			} else if (d[i] <= lastO2) {
				lastO2 = d[i];
			}
		}
		
		int lastA = *min_element(a.begin(), a.end());
		if (lastA < lastO2) cout << "Y" << endl;
		else cout << "N" << endl;
	}
}