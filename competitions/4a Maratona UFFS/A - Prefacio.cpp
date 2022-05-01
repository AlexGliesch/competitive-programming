#include <iostream>
#include <cmath>
#include <string>

using namespace std;

int euclidean_mod(int a, int b) {
	int r = a % b;
	return r >= 0 ? r : r + std::abs(b);
}

int euclidean_div(int a, int b) {
	return (a - euclidean_mod(a, b)) / b;
}

int main() {
	int a, b; cin >> a >> b;	
	if (b == 0) {
		cout << "0 " << a << endl;
	} else {
		cout << euclidean_div(a, b) << " " << euclidean_mod(a, b) << endl;
	}
}
