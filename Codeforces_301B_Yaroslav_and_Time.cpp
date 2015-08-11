#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
using namespace std;

const int MAXN = 110;
int n, d, a[MAXN], x[MAXN], y[MAXN], graph[MAXN][MAXN];

int main() {
    scanf("%d%d", &n, &d);
    for (int i = 2; i <= n-1; i++) {
        scanf("%d", &a[i]);
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &x[i], &y[i]);
    }

    memset(graph, 0x3f, sizeof(graph));
    for (int i = 1; i <= n; i++) {
        for (int j = i+1; j <= n; j++) {
            int dis = d * (abs(x[i] - x[j]) + abs(y[i] - y[j]));
            graph[i][j] = dis - a[j];
            graph[j][i] = dis - a[i];
        }
    }
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
            }
        }
    }

    printf("%d\n", graph[1][n]);
    return 0;
}
