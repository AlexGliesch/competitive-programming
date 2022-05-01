#include <map>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	map<string, int> m;
	vector<string> died;
	string a, b;
	while (cin >> a >> b) {
		m[a]++;
		died.push_back(b);
	}
	for (auto& s : died) m.erase(s);
	cout << "HALL OF MURDERERS" << endl;
	for (auto& p : m) {
		cout << p.first << " " << p.second << endl;
	}
}