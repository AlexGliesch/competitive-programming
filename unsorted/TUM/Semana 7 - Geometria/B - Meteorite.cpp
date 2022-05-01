#include <cmath>
#include <cstdio>

int nxt[2010][2010][2], t, px, py, n, fx, fy, x, y, nx, ny;

int cross(int qx, int qy, int rx, int ry) { return (qx - px) * (ry - py) - (qy - py) * (rx - px); }

double angle(int qx, int qy, int rx, int ry) {
	int ux = qx - px, uy = qy - py, vx = rx - px, vy = ry - py;
	return acos(double(ux * vx + uy * vy) / sqrt(double(ux * ux + uy * uy) * (vx * vx + vy * vy)));
}

int main() {
	scanf("%d", &t);
	for (int T = 1; T <= t; ++T) {
		printf("Case #%d: ", T);
		scanf("%d %d %d", &px, &py, &n);
		px += 1000, py += 1000;
		for (int i = 0; i < n; ++i) {
			int x1, y1, x2, y2;
			scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
			x1 += 1000, y1 += 1000, x2 += 1000, y2 += 1000;
			nxt[x1][y1][0] = x2;
			nxt[x1][y1][1] = y2;
			if (i == 0) fx = x1, fy = y1;
		}
		double sum = 0;
		x = fx, y = fy;
		do {
			nx = nxt[x][y][0], ny = nxt[x][y][1];
			double ang = angle(x, y, nx, ny);
			sum += (cross(x, y, nx, ny) < 0 ? -ang : ang);
			x = nx, y = ny;
		} while (!(x == fx && y == fy));
		if (fabs(sum - 2 * M_PI) < 1e-6 || fabs(sum + 2 * M_PI) < 1e-6)
			printf("jackpot\n");
		else
			printf("too bad\n");
	}
}