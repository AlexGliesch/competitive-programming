#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/* 
* Greedy solution: repeatedly search for the emoticon in the string with the
* lowest match end index E, and remove from the string all characters up
* until E. Stop when no emoticon is found on the string anymore.
* 
* (ps: I got the idea from the Internet, don't fully understand it)
*/

vector<string> emoticons;
int N, M, ans;

int main() {
	string line; 
	while (cin >> N >> M, N and M) {
		getline(cin, line);
		emoticons.clear(); emoticons.resize(N);		
		for (int i = 0; i < N; ++i) getline(cin, emoticons[i]);

		ans = 0;
		for (int i = 0; i < M; ++i) {
			getline(cin, line);
			size_t pos = 0;
			while (true) {				
				size_t min_index = (1<<28);
				for (int j = 0; j < N; ++j) {
					size_t index = line.find(emoticons[j], pos);
					if (index != string::npos) {
						min_index = min(min_index, 
										index + emoticons[j].size());
					}
				}
				if (min_index == (1<<28)) break;
				pos = min_index;
				++ans;				
			}
		}

		cout << ans << endl;
	}
}