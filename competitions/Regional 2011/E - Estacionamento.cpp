#include <iostream>
#include <vector>
#include <ciso646>

using namespace std;

/* just solve it using vector operations, nothing special. */

struct Car {
	Car(int plate, int begin, int end)
		: plate(plate), begin(begin), end(end) {
	}
	int plate, begin, end;
};

int main() {
	int C, N;;
	while (cin >> C >> N) {
		vector<Car> car;
		int ans = 0;
		car.push_back(Car(-1, -1, 0)); /* dummy car in the beginning */
		car.push_back(Car(-1, C, C + 1)); /* dummy car at the end */
		for (int i = 0; i < N; ++i) {
			char c; int p, q;
			cin >> c;
			if (c == 'C') {
				cin >> p >> q;
				for (int i = 0; i < car.size() - 1; ++i) {
					if (car[i + 1].begin - car[i].end >= q) {
						car.insert(car.begin() + i + 1, 
							Car(p, car[i].end, car[i].end + q));
						ans++;
						break;
					}
				}
			} else if (c == 'S') {
				cin >> p;
				for (int i = 1; i < car.size() - 1; ++i) {
					if (car[i].plate == p) 
						car.erase(car.begin() + i);
				}
			}
		}
		cout << ans * 10 << endl;
	}
}