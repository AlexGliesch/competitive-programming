#include <string>
#include <iostream>

using namespace std;

/* just write some if's. */

int main(){
	int N; 
	while (cin >> N, N) {		
		string s; cin >> s;
		char facing = 'N';
		for (int i = 0; i < s.size(); ++i) {
			char c = s[i];
			if (c == 'D') {
				if (facing == 'N') facing = 'L';
				else if (facing == 'L') facing = 'S';
				else if (facing == 'S') facing = 'O';
				else if (facing == 'O') facing = 'N';
			} else if (c == 'E') {
				if (facing == 'N') facing = 'O';
				else if (facing == 'L') facing = 'N';
				else if (facing == 'S') facing = 'L';
				else if (facing == 'O') facing = 'S';
			}
		}
		cout << facing << endl;
	}
}