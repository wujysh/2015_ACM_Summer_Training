#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

const int MAXN = 110;
const int dx[8] = {0, -1, 0, 1, -1, -1, 1, 1};
const int dy[8] = {-1, 0, 1, 0, -1, 1, -1, 1};

int n, m, ans;
char graph[MAXN][MAXN];
bool visited[MAXN][MAXN];

void init() {
    ans = 0;
    memset(visited, false, sizeof(visited));
}

void input() {
    getchar();
    for (int i = 0; i < m; i++) {
        scanf("%s", graph[i]);
    }
}

int dfs(int x, int y) {
    int cnt = 1;
    for (int i = 0; i < 8; i++) {
        int nx = x + dx[i], ny = y + dy[i];
        if (nx < 0 || ny < 0 || nx >= m || ny >= n || graph[nx][ny] == '*') continue;
        if (!visited[nx][ny]) {
            visited[nx][ny] = true;
            cnt += dfs(nx, ny);
        }
    }
    return cnt;
}

void solve() {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (!visited[i][j] && graph[i][j] == '@') {
                visited[i][j] = true;
                dfs(i, j);
                ans++;
            }
        }
    }

    printf("%d\n", ans);
}

int main() {
    while (~scanf("%d%d", &m, &n) && (m || n)) {
        init();
        input();
        solve();
    }
    return 0;
}
