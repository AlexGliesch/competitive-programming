#include <iostream>
#include <cmath>

using namespace std;

/* just check if the coast guard can reach the international waters 
 * perpendicualr to the bandit's position before the bandits. */

int main() {
	double D, Vf, Vg;
	while (cin >> D >> Vf >> Vg) {
		if ((12.0 / Vf) >= (sqrt(144 + D*D) / Vg)) {
			cout << 'S' << endl;
		} else {
			cout << 'N' << endl;;
		}
	}
}