#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

const int MAXN = 510;
bool graph[MAXN][MAXN];
int nCase, n, m, ans;

void init() {
    memset(graph, false, sizeof(graph));
    ans = 0;
}

void input() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        graph[a][b] = true;
    }
}

void solve() {
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            if (!graph[i][k]) continue;
            for (int j = 1; j <= n; j++) {
                if (!graph[k][j]) continue;
                graph[i][j] = true;
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = i+1; j <= n; j++) {
            if (!graph[i][j] && !graph[j][i]) {
                ans++;
            }
        }
    }
    printf("%d\n", ans);
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
