#include <iostream>
#include <string>
#include <ciso646>
#include <algorithm>

using namespace std;

/* 
 * Straightforward problem, use normal simulation.
 * Take the minimum DIFFERENCE, not the subtraction. That is, use modules. * 
 * */

int rank_val[300], suit_val[300];
string ranks = "4567QJKA23", suits = "DSHC";

struct Card {
	Card() { }
	Card(const string& s) : rank(rank_val[s[0]]), suit(suit_val[s[1]]) { }
	char rank, suit;
};

Card first;

bool card_less(Card a, Card b) {
	if (a.rank == first.rank) {
		return (b.rank == first.rank) and a.suit < b.suit;
	}
	if (b.rank == first.rank) return true;
	return a.rank < b.rank;
}

bool card_equal(Card a, Card b) {
	return not card_less(a, b) and not card_less(b, a);
}

int main() {
	int n; cin >> n;
	string s; cin >> s;
	string names[4];

	for (int i = 0; i < ranks.size(); ++i) 
		rank_val[ranks[i]] = i;

	for (int i = 0; i < suits.size(); ++i) 
		suit_val[suits[i]] = i;


	first = Card(s);
	first.rank = (first.rank + 1) % ranks.size();
	int win[4];
	for (int i = 0; i < 4; ++i) {
		cin >> names[i] >> win[i];
	}

	Card cards[4];
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < 4; ++j) {
			cin >> s; cards[j] = Card(s);
		}

		Card* c = max_element(cards, cards + 4, card_less);
		int ct = count_if(cards, cards + 4, 
			[=](Card a) { return card_equal(a, *c); });
		
		if (ct == 1) --win[c - cards];
	}

	int* m = min_element(win, win + 4, [](int a, int b) { 
		return abs(a) < abs(b); });
	int ct = count(win, win + 4, *m);
	cout << ((ct == 1) ? names[m - win] : "*") << endl;
}