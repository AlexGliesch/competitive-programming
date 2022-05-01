#include <iostream>
#include <string>

using namespace std;
using ll = long long;

ll where(string s) {
	ll n = s.size();
	ll lo = 0, hi = (1LL << n)-1;
	bool invert = false;
	for (ll i = 0; i < n; ++i) {
		cout << "hi: " << hi << ", lo: " << lo << endl;
		cout << "invert: " << invert << endl;
		if (s[i] == '0') {
			if (invert)lo = (hi + lo) / 2;
			else hi = (hi + lo) / 2;
// 			invert = false;
		} else {
			if (invert)hi = (hi + lo) / 2;
			else lo = (hi + lo) / 2; 
			invert = !invert;
		}
	}
	cout << "hi: " << hi << ", lo: " << lo << endl;
	return	hi;
}

int main() {
	ll n; cin >> n;
	string a, b; cin >> a >> b;
	ll wa = where(a);
	ll wb = where(b);
	cout << wb-wa-2 << endl;
	
}