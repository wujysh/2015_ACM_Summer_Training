#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
using namespace std;

const int MAXN = 110;
int n, color[MAXN], graph[MAXN][MAXN];
bool isFailed;

void init() {
    memset(graph, false, sizeof(graph));
    memset(color, -1, sizeof(color));
    isFailed = false;
}

void input() {
    for (int u = 1; u <= n; u++) {
        int v;
        while (~scanf("%d", &v) && v) {
            graph[u][v] = graph[v][u] = true;
        }
    }
}

void dfs(int u, int c) {
    if (isFailed) return;
    if (color[u] != -1) {  // colored
        if (color[u] == c) {  // correct
            return;
        } else {  // conflict
            isFailed = true;
            return;
        }
    }
    color[u] = c;
    for (int v = 1; v <= n; v++) {
        if (graph[u][v]) {
            graph[u][v] = graph[v][u] = false;
            dfs(v, 1-c);
        }
    }
}

void solve() {
    for (int i = 1; i <= n; i++) {
        if (!isFailed && color[i] == -1) {
            dfs(i, 0);
        }
    }
    if (isFailed) {
        printf("-1\n");
    } else {
        for (int i = 1; i <= n; i++) {
            printf("%d", color[i]);
        }
        printf("\n");
    }
}

int main() {
    while (~scanf("%d", &n) && n) {
        init();
        input();
        solve();
    }
    return 0;
}
