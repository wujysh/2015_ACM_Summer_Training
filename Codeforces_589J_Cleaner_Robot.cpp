#include <bits/stdc++.h>
using namespace std;

const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

const int MAXN = 15;

char graph[MAXN][MAXN];
bool visited[MAXN][MAXN][4], vis[MAXN][MAXN];
int w, h, initial_x, initial_y, initial_direct, ans;

void init() {
    memset(visited, false, sizeof(visited));
    memset(vis, false, sizeof(vis));
    ans = 0;
}

void input() {
    for (int i = 0; i < w; i++) {
        scanf("%s", graph[i]);
        for (int j = 0; j < h; j++) {
            if (graph[i][j] == 'U') {
                initial_direct = 0;
                initial_x = i;
                initial_y = j;
            } else if (graph[i][j] == 'R') {
                initial_direct = 1;
                initial_x = i;
                initial_y = j;
            } else if (graph[i][j] == 'D') {
                initial_direct = 2;
                initial_x = i;
                initial_y = j;
            } else if (graph[i][j] == 'L') {
                initial_direct = 3;
                initial_x = i;
                initial_y = j;
            }
        }
    }
}

void solve() {
    int x = initial_x, y = initial_y, direct = initial_direct;
    while (true) {
        visited[x][y][direct] = true;
        if (!vis[x][y]) {
            vis[x][y] = true;
            ans++;
        }

        bool flag = true;
        int cnt = 0;
        while (true) {
            if (++cnt == 5) {
                flag = false;
                break;
            }
            int nx = x + dx[direct], ny = y + dy[direct];
            if (nx < 0 || ny < 0 || nx >= w || ny >= h || graph[nx][ny] == '*') {
                direct = (direct + 1) % 4;
            } else {
                if (visited[nx][ny][direct]) {
                    flag = false;
                    break;
                }
                x = nx;
                y = ny;
                break;
            }
        }
        if (!flag) {
            break;
        }
    }

    printf("%d\n", ans);
}

int main() {
    while (~scanf("%d%d", &w, &h)) {
        init();
        input();
        solve();
    }
    return 0;
}
