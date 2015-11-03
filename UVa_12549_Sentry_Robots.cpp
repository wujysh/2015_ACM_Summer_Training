#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

const int MAXN = 110;
const int MAXM = 2010;

int n, m, nCase, cCase, graph[MAXN][MAXN], idx[MAXN][MAXN], idy[MAXN][MAXN];
bool G[MAXM][MAXM], visited[MAXM];
int link[MAXN], X, Y;

void init() {
    memset(G, false, sizeof(G));
    memset(graph, 0, sizeof(graph));
}

void input() {
    scanf("%d%d", &n, &m);
    int p, x, y;
    scanf("%d", &p);
    while (p--) {
        scanf("%d%d", &x, &y);
        graph[x][y] = 1;
    }
    scanf("%d", &p);
    while (p--) {
        scanf("%d%d", &x, &y);
        graph[x][y] = 2;
    }
}

bool dfs(int u) {
    for (int v = 0; v < Y; v++) {
        if (G[u][v] && !visited[v]) {
            visited[v] = true;
            if (link[v] == -1 || dfs(link[v])) {
                link[v] = u;
                return true;
            }
        }
    }
    return false;
}

int hungary() {
    int ans = 0;
    memset(link, -1, sizeof(link));
    for (int u = 0; u < X; u++) {
        memset(visited, false, sizeof(visited));
        if (dfs(u)) {
            ans++;
        }
    }
    return ans;
}

void solve() {
    int row_num = -1, col_num = -1;
    for (int i = 1; i <= n; i++) {
        bool flag = true;
        for (int j = 1; j <= m; j++) {
            if (graph[i][j] == 1) {
                if (flag) {
                    row_num++;
                }
                idx[i][j] = row_num;
                flag = false;
            } else if (graph[i][j] == 2) {
                flag = true;
            }
        }
    }
    for (int j = 1; j <= m; j++) {
        bool flag = true;
        for (int i = 1; i <= n; i++) {
            if (graph[i][j] == 1) {
                if (flag) {
                    col_num++;
                }
                idy[i][j] = col_num;
                flag = false;
            } else if (graph[i][j] == 2) {
                flag = true;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (graph[i][j] == 1) {
                G[idx[i][j]][idy[i][j]] = true;
            }
        }
    }
    X = row_num + 1;
    Y = col_num + 1;

    printf("%d\n", hungary());
}

int main() {
    scanf("%d", &nCase);
    while (nCase--) {
        init();
        input();
        solve();
    }
    return 0;
}
