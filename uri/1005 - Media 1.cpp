#include <cmath>
#include <iostream>
#include <iomanip>

using namespace std;

int main() {
	double a, b;
	cin >> a >> b;
	cout << "MEDIA = " << setprecision(5) << fixed 
		<< min(10.0, (0.35 * a + 0.75 * b) / 1.1) << endl;
}