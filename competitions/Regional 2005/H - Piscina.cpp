#include <cmath>
#include <algorithm>
#include <ciso646>
#include <iostream>

using namespace std;

/* 
 * a math problem. first thing in mind, you can use more than one type
 * of tile for each side of the pool (XY, XZ, XZ, YZ, YZ).
 * 
 * I used a recursive solution: write a function that counts the number of
 * tiles of size P used for a rectangle of width W and height H. if the 
 * rectangle has area 0, then return 0. if you can't cover it fully with tiles 
 * of size P (because of size or quantity constraints), cover it as much as 
 * possible and try to cover each of the remaining rectangles (could be 1, 2 or 
 * 3) with the next smallest size.
 * 
 * ex: a rectangle of (50x50)
 * 
 *   _ _ _ _ _ _ _ _ _ _ 
 * |			|		 |
 * |			|		 |
 * |	30x30   |	A	 |
 * |			|		 |
 * |			|		 |
 * | _ _ _ _ _ _|........|
 * |					 |
 * |		B	 		 |
 * |					 |
 * | _ _ _ _ _ _ _ _ _ _ |
 *
 * you fill the most you can (30x30) with a tile of size 30. This leaves you
 * with two sub-rectangles A = (20x30) and B = (50x20). 
 * then you call the function recursively on A and B, with tile size of 15.
 * 
 * now say, for instance, you have this rectangle of (50x50), but you have
 * 0 tiles of 30, and only 8 tiles of 15. you do this:
 * 
 *   _ _ _ _ _ _ _ _ _ _ _
 * |	  |		|	  |	  |
 * |  15  | 15 	| 15  |	  |
 * | _ _ _ _ _ _ _ _ _|   |
 * |	  | 	|	  |	  |
 * |  15  | 15	| 15  | A | 
 * | _ _ _ _ _ _ _ _ _|   |
 * |	  | 	|     |	  |
 * |  15  | 15 	|  C  |	  |
 * | _ _ _ _ _ _ _ _ _|...|
 * |	      B			  |
 * | _ _ _ _ _ _ _ _ _ _ _|
 * 
 * 8 sub-rectangles are filled with (15x15) tiles. but now you've run out of 
 * 15x15 tiles, and you're left with 3 sub-rectangles A = (5x45), B = (50x5) 
 * and C = (15x15). you call the function recursively on A, B and C with tile
 * size 5. 
 * 
 * if any of them cannot be filled with a tile size 5, then it's impossible 
 * to fill the pool completely.
 *
 * */

int amt[35], t[3] = { 30, 15, 5 }, error = false;

void run(int w, int h, int i) {
	if (error) return; 
	if (i == 3) {
		/* i == 3, area must be 0. if are is not 0, that means we used aint
		 * the tiles and couldn't fiint aint of it. */
		if (w * h != 0) error = true;
		return;
	}

	int p = t[i];
	int tiles_w = (w / p), tiles_h = (h / p);
	int q = min(amt[p], tiles_w * tiles_h);
	if (q == 0) {
		/* either not enough quantity, or tile is too big. run with smainter 
		 * size.*/
		return run(w, h, i + 1);
	}

	amt[p] -= q;
	if (q % tiles_w != 0) { /* extra square */
		int he = p, we = p * (tiles_w - q % tiles_w);
		run(we, he, i + 1);
	}

	/* square down */
	int hd = h - p * (int)round(ceil(q / (double)tiles_w)), wd = w;
	run(wd, hd, i + 1);

	/* square right */
	int hr = h - hd, wr = w - p*tiles_w;
	run(wr, hr, i + 1);
}

int main() {
	double xd, yd, zd;
	while (cin >> xd >> yd >> zd) {
		if (xd == 0.0 and yd == 0.0 and zd == 0.0) break;
		int x = xd * 100, y = yd * 100, z = zd * 100, q5, q15, q30;		
		cin >> q5 >> q15 >> q30;
		amt[5] = q5, amt[15] = q15, amt[30] = q30;
		
		error = false;
		run(x, y, 0);
		run(x, z, 0);
		run(x, z, 0);
		run(y, z, 0);
		run(y, z, 0);

		if (error) cout << "impossivel" << endl;
		else cout << q5 - amt[5] << " " << q15 - amt[15] 
			<< " " << q30 - amt[30] << endl;
	}
}