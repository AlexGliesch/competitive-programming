#include <string>
#include <iostream>

using namespace std;

int main() {
	string s = "LIFE IS NOT A PROBLEM TO BE SOLVED    ";
	int N; cin >> N;
	cout << string(s, 0, N) << endl;
}

