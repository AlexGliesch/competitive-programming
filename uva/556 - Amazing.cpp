#include <algorithm>
#include <ciso646>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/* Quite hard problem, requires A LOT of attention to detail. I solved it
 * by storing the position of the robot, the direction it's going, and the
 * position of the wall next to it. I believe the wall position may be
 * reduntant given the robot's position and direction, though, but I was too
 * bored to simplify it.
 *
 * The algorithm I used goes like this:
 * if the robot can go straight:
 *		go straight
 *		if the wall it was following isn't there anymore:
 *			turn in the direction of the wall it was following
 *			(don't forget to update position and direction)
 * else (if it can't go straight):
 *		turn in the opposite direction of the wall it's following
 * */

int b, w, r, c, dr, dc, wr, wc;
vector<string> maze;
vector<vector<int>> visited;
vector<int> freq;

bool valid(int r, int c) {
  if (r >= b or r < 0)
    return false;
  if (c >= w or c < 0)
    return false;
  return maze[r][c] == '0';
}

void walk() {
  r += dr, c += dc;
  --freq[visited[r][c]];
  ++freq[visited[r][c] + 1];
  ++visited[r][c];
}

int main() {
  ios_base::sync_with_stdio(false);
  while (cin >> b >> w, b and w) {
    maze.resize(b);
    visited.assign(b, vector<int>(w, 0));
    freq.assign(5, 0);

    r = b - 1, c = 0; /* robot position */
    dr = 0, dc = 1;   /* direction the robot is walking */
    wr = b, wc = 0;   /* position of the wall it's following*/

    for (int i = 0; i < b; ++i) {
      cin >> maze[i];
      freq[0] += count(begin(maze[i]), end(maze[i]), '0');
    }

    while (true) {
      if (valid(r + dr, c + dc)) {
        /* if robot can go straight (and wall is to the right),
         * keep going straight. */
        walk();
        if (r == b - 1 and c == 0)
          break;
        if (valid(wr + dr, wc + dc)) {
          /* wall disappeared, robot must turn and walk to follow
           * the wall. */
          dr = wr - (r - dr), dc = wc - (c - dc);
          walk();
          if (r == b - 1 and c == 0)
            break;
        } else {
          /* wall is in the same place, keep going. */
          wr += dr, wc += dc;
        }
      } else { /* hit a wall. turn in the direction opposite the current
                       wall. */
        int nr = r + dr, nc = c + dc;
        dr = r - wr, dc = c - wc;
        wr = nr, wc = nc;
      }
    }

    cout << setfill(' ');
    for (auto i : freq)
      cout << setw(3) << i;
    cout << endl;
  }
}