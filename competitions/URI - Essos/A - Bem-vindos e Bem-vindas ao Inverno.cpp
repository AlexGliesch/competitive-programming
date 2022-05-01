#include <iostream>
#include <ciso646>

using namespace std;

int main() {
	int a, b, c;
	cin >> a >> b >> c; 
	if (a > b and b <= c) cout << ":)" << endl;
	else if (a < b and b >= c) cout << ":(" << endl;
	else if (a < b and b < c and c - b < b - a) cout << ":(" << endl;
	else if (a < b and b < c and c - b >= b - a) cout << ":)" << endl;
	else if (a > b and b > c and b - c < a - b) cout << ":)" << endl;
	else if (a > b and b > c and b - c >= a - b) cout << ":(" << endl;
	else if (a == b and b < c) cout << ":)" << endl;
	else if (a == b and b >= c) cout << ":(" << endl;
}