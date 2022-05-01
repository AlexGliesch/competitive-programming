#include <iostream>
#include <string>

using namespace std;

/* Easy. Create a look-up table for the number of leds for each digit, parse 
 * the string, and add the solution. */

int leds[] = { 6, 2, 5, 5, 4, 5, 6, 3, 7, 6 };

int main() {
	int t; cin >> t;
	for (int i = 0; i < t; ++i) {
		string s; cin >> s;
		int x = 0;
		for (const auto& c : s) 
			x += leds[c - '0'];
		cout << x << " leds" << endl;
	}
}