#include <stdio.h>
#include <string.h>

char in[16][16], dr[] = {0, 0, -1, 1}, dc[] = {-1, 1, 0, 0};
int g[64][4], t, w, h, num_tools, start, is_tool[64], visited[64];

int DFS(int v, int parent, int tools) {
	if (is_tool[v]) --tools;
	if (tools == 0) return 1;
	visited[v] = tools;
	for (int i = 0; i < 4; ++i) {
		int u = g[v][i];
		if (u != -1)
			if (visited[u] == -1 && DFS(u, v, tools))
				return 1;
			else if (visited[u] == tools && u != parent)
				break;
	}
	visited[v] = -1;
	return 0;
}

int main() {
	scanf("%d", &t);
	for (int k = 1; k <= t; ++k) {
		scanf("%d %d", &w, &h);
		for (int i = 0; i < h; ++i)
			scanf("%s", in[i]);

		int nt = 0, v_num = 0, vx[16][16];
		memset(is_tool, 0, sizeof is_tool);
		for (int i = 0; i < h; ++i)
			for (int j = 0; j < w; ++j)
				if (in[i][j] != '#') {
					if (in[i][j] == 'L') {
						start = v_num;
					} else if (in[i][j] == 'T') {
						is_tool[v_num] = 1;
						++nt;
					}
					vx[i][j] = v_num++;
				}

		memset(g, -1, sizeof g);
		for (int i = 0; i < h; ++i)
			for (int j = 0; j < w; ++j)
				if (in[i][j] != '#')
					for (int l = 0; l < 4; ++l) {
						int ni = i + dr[l], nj = j + dc[l];
						if (ni >= 0 && ni < h && nj >= 0 && nj < w && in[ni][nj] != '#') {
							g[vx[i][j]][l] = vx[ni][nj];
						}
					}

		memset(visited, -1, sizeof visited);
		printf("Case #%d: %s\n", k, DFS(start, -1, nt) ? "yes" : "no");
	}
}