#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
using namespace std;

const int MAXN = 100;
const int MAXM = MAXN * 2 + 1;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, -1, 0, 1};

int n, t, graph[MAXM][MAXM], t_graph[MAXM][MAXM];

int main() {
    scanf("%d%d", &n, &t);

    graph[MAXN][MAXN] = n;  // (0, 0)
    bool found = n > 0;
    while (found) {
        found = false;
        memset(t_graph, 0, sizeof(t_graph));
        for (int i = 0; i < MAXM; i++) {
            for (int j = 0; j < MAXM; j++) {
                if (graph[i][j] >= 4) {
                    found = true;
                    for (int k = 0; k < 4; k++) {
                        int nx = i + dx[k], ny = j + dy[k];
                        t_graph[nx][ny] += graph[i][j] / 4;
                    }
                }
                t_graph[i][j] += graph[i][j] % 4;
            }
        }
        memcpy(graph, t_graph, sizeof(graph));
    }

    for (int i = 0; i < t; i++) {
        int x, y, ans;
        scanf("%d%d", &x, &y);
        if (abs(x) > MAXN || abs(y) > MAXN) {
            ans = 0;
        } else {
            ans = graph[x + MAXN][y + MAXN];
        }
        printf("%d\n", ans);
    }

    return 0;
}
