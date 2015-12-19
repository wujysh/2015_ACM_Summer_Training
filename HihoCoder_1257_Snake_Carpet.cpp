#include <bits/stdc++.h>
using namespace std;

const int MAXN = 510;
const int dx[4] = {0, 0, 1, -1};
const int dy[4] = {1, -1, 0, 0};

int n, H[MAXN], W[MAXN];
int visited[MAXN][MAXN],marked;
vector<pair<int, int> > ans[MAXN];
vector<vector<int> > g[MAXN];

void rotate(int id, int x1, int x2, int h) {
	for (int i = 1; i <= h; i++) {
		for (int j = x1; j <= x2; j++) {
			g[id][x2-j+1][i] = g[id-1][i][j];
		}
	}
}

void movL(int id, int x1, int x2, int h) {
	for (int i = h; i >= 1; i--) {
		for (int j = x1; j <= x2; j++) {
			g[id][i+1][j-1] = g[id-1][i][j];
		}
	}
}

void movR(int id, int x1, int x2, int h) {
	for (int i = 1; i <= h; i++) {
		for (int j = x2; j >= x1; j--) {
			g[id][i][j+2] = g[id-1][i][j];
		}
	}
}

void add1(int id, int x1, int x2, int h) {
	for (int j = x1; j <= x2; j++) {
		g[id][1][j] = id;
	}
	for (int i = 2; i <= h; i++) {
		g[id][i][x2] = id;
	}
}

void add2(int id, int x1, int x2, int h) {
	for (int i = 1; i <= h; i++) {
		for (int j = x1; j <= x2; j++) {
			g[id][i][j] = id;
		}
	}
}

void copy(int id, int x1, int x2, int h) {
	for (int i = 1; i <= h; i++) {
		for (int j = x1; j <= x2; j++) {
			g[id][i][j]= g[id-1][i][j];
		}
	}
}

void dfs(int x, int y, int color, int id) {
	ans[color].push_back(make_pair(x, y));
	
	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i], ny = y + dy[i];
		if (nx < 1 || ny < 1 || nx > H[id] || ny > W[id]) continue;
		if (visited[nx][ny] != marked && g[n][nx][ny] == color) {
			visited[nx][ny] = marked;
			dfs(nx, ny, color, id);
		}
	}
}

void calc(int n){
	for (int i = 1; i <= n; i++) {
		ans[i].clear();
	}
	
	marked++;
	for (int i = 1; i <= H[n]; i++) {
		for (int j = 1; j <= W[n]-H[n]; j++) {
			if (visited[i][j] != marked) {
				visited[i][j] = marked;
				dfs(i, j, g[n][i][j], n);
			}
		}
	}
}

void debug(int n) {
	for (int i = 1; i <= H[n]; i++) {
		for (int j = 1; j <= W[n]; j++) {
			printf("%d ", g[n][i][j]);
		}
		printf("\n");
	}
}

void init(){
	H[3] = 2;  W[3] = 3;
	g[3].resize(H[3]+1);
	for (int i = 1; i <= H[3]; i++) {
		g[3][i].resize(W[3]+1);
	}
	g[3][1][1] = 2;  g[3][1][2] = 3;  g[3][1][3] = 3;
	g[3][2][1] = 2;  g[3][2][2] = 1;  g[3][2][3] = 3;
	
	H[4] = 2;  W[4] = 5;
	g[4].resize(H[4]+1);
	for (int i = 1; i <= H[4]; i++) {
		g[4][i].resize(W[4]+1);
	}
	g[4][1][1] = 4;  g[4][1][2] = 4;  g[4][1][3] = 2;  g[4][1][4] = 3;  g[4][1][5] = 3;
	g[4][2][1] = 4;  g[4][2][2] = 4;  g[4][2][3] = 2;  g[4][2][4] = 1;  g[4][2][5] = 3;
	
	for (int i = 5; i <= 500; i++) {
		H[i] = (i + 1) / 2;
		W[i] = (1 + i) * i / 2 / H[i];
		g[i].resize(H[i]+1);
		for (int j = 1; j <= H[i]; j++) {
			g[i][j].resize(W[i]+1);
		}
		
		if (i % 2 == 1) {  // even
			rotate(i, 1, i / 2 + 1, H[i-1]);
			movL(i, i / 2 + 2, W[i-1], H[i-1]);
			add1(i, i / 2 + 1, W[i], H[i]);
		} else {  // odd
			movR(i, i / 2, W[i-1], H[i-1]);
			add2(i, i / 2, i / 2 + 1, H[i]);
			copy(i, 1, i / 2 - 1, H[i-1]);
		}
	}
}

void solve() {
	if (n <= 2) {
		if (n == 1) {
			printf("1 1\n");
			printf("1 1\n");
		} else if (n == 2) {
			printf("1 3\n");
			printf("1 1\n1 2 1 3\n");
		}
	} else {
		printf("%d %d\n", H[n], W[n]);
		
		//~ debug(n);
		
		calc(n);
		
		for (int i = 1; i <= n; i++) {
			if (i & 1) {
				for (int j = 1; j <= (i+1)/2; j++) {
					if (j > 1) printf(" ");
					printf("%d %d", H[n]-(i-1)/2, W[n]-H[n]+j);
				}
				for (int j = H[n]-(i-1)/2+1; j <= H[n]; j++) {
					printf(" %d %d", j, W[n]-H[n]+(i+1)/2);
				}
				printf("\n");
			} else {
				for (int j = 0; j < (int)ans[i].size(); j++) {
					if (j > 0) printf(" ");
					printf("%d %d", ans[i][j].first, ans[i][j].second);
				}
				printf("\n");
			}
		}
	}
}

int main() {
	init();
	while (~scanf("%d", &n)) {
		solve();
	}
	return 0;
}
