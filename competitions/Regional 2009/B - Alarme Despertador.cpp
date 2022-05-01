#include <iostream>
#include <ciso646>

using namespace std;

/* 
 * Just convert it all to minutes. 
 * */

int main() {
	int H1, M1, H2, M2;
	while (cin >> H1 >> M1 >> H2 >> M2, H1 or M1 or H2 or M2) {
		int Mbefore = H1 * 60 + M1;
		int Mafter = H2 * 60 + M2;
		if (Mafter < Mbefore) Mafter += 24 * 60;
		cout << Mafter - Mbefore << endl;
	}
}