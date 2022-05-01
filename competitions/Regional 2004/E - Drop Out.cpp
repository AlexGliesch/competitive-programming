#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

/*
 * detail that they don't say in the description: if all players are dealt the
 * same card, the game stops immediately and ALL OF THEM win. This rule is 
 * necessary for sample input #1 to pass.
 * 
 * other than that, straightforward problem. keep an array that says whether a 
 * player is active or not.
 */

int main() {
	int N;
	while (cin >> N, N) {
		vector<string> names(N);
		for (int i = 0; i < N; ++i) {
			cin >> names[i];
		}

		vector<int> deck(52);
		for (int i = 0; i < 52; ++i) cin >> deck[i];

		vector<bool> active(N, true);
		vector<int> dealt(N);
		int num_active = N;
		int i = 0;
		while (i < 52) {
			if (i + num_active > 52) {
				break;
			}
			if (num_active == 1) break;

			int min_dealt = -1, num_min_dealt = 0, num_cards_dealt = 0;
			for (int j = 0; j < N; ++j) {
				if (active[j]) {
					dealt[j] = deck[i + num_cards_dealt++];
					if (min_dealt == -1 or min_dealt > dealt[j])
						min_dealt = dealt[j];
				}
			}

			for (int j = 0; j < N; ++j) {
				if (active[j] and dealt[j] == min_dealt) {
					++num_min_dealt;
				}
			}

			if (num_min_dealt < num_active) {
				for (int j = 0; j < N; ++j) {
					if (active[j] and dealt[j] == min_dealt) {
						active[j] = false;
						--num_active;
					}
				}
			} else break;
			i += num_cards_dealt;
		}

		for (int i = 0; i < N; ++i) {
			if (active[i]) cout << names[i] << " ";
		}
		cout << endl;
	}
}