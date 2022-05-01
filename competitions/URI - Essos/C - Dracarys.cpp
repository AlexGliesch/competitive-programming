#include <iostream>
#include <algorithm>

using namespace std;

int main() {
	int a, b, c, d;
	cin >> a >> b >> c >> d;
	int side = min(min(a, b) + min(c, d), min(max(a, b), max(c, d)));
	cout << side*side << endl;
}