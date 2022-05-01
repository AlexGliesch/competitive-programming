#include <iostream>
#include <queue>

using namespace std;

/* just pop the first card, print it, then pop the second and add
 * it to end of the queue. do this until there are more than 1 cards on the
 * deck.
 *
 * watch out for a corner case: if n == 1, you can't do any operations!
 * */

int main() {
  ios_base::sync_with_stdio(false);
  int n;
  while (cin >> n, n) {
    if (n == 1) {
      cout << "Discarded cards:" << endl << "Remaining card: 1" << endl;
      continue;
    }
    queue<int> q;
    for (int i = 2; i <= n; ++i)
      q.push(i);
    cout << "Discarded cards: 1";
    while (q.size() > 1) {
      q.push(q.front());
      q.pop();
      cout << ", " << q.front();
      q.pop();
    }
    cout << endl << "Remaining card: " << q.front() << endl;
  }
}