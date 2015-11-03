#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
using namespace std;

const int MAXN = 1010;
const int MAXM = 500010;
const double EPS = 1e-10;
const double INF = 1e70;

double dis[MAXN][MAXN], C[MAXN][MAXN], D[MAXN][MAXN], tc[MAXN], td[MAXN], t[MAXN];
int u[MAXM], v[MAXM], c[MAXM], d[MAXM], cnt;
bool vis[MAXN];

double prim(int n) {
    double x = 0, y = 0;
    for (int i = 1; i <= n; i++) {
        t[i] = dis[1][i];
        vis[i] = false;
        tc[i] = C[1][i];
        td[i] = D[1][i];
    }

    vis[1] = true;
    for (int i = 1; i < n; i++) {
        double mi = INF;
        int k = 1;
        for (int j = 1; j <= n; j++) {
            if (!vis[j] && mi > t[j]) {
                mi = t[j];
                k = j;
            }
        }
        vis[k] = true;
        x += tc[k];
        y += td[k];
        for (int j = 1; j <= n; j++) {
            if (!vis[j] && dis[k][j] < t[j]) {
                t[j] = dis[k][j];
                td[j] = D[k][j];
                tc[j] = C[k][j];
            }
        }
    }
    return y / x;
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            dis[i][j] = INF;
        }
    }

    double rate = 1e20, pre;
    for (int i = 0; i < m; i++) {
        scanf("%d%d%d%d", u + i, v + i, c + i, d + i);
        C[u[i]][v[i]] = C[v[i]][u[i]] = c[i];
        D[u[i]][v[i]] = D[v[i]][u[i]] = d[i];
    }

    rate = 1.0;
    cnt = 0;
    while (true) {
        pre = rate;
        cnt++;
        for (int i = 0; i < m; i++) {
            dis[u[i]][v[i]] = dis[v[i]][u[i]] = d[i] - rate * c[i];
        }
        rate = prim(n);
        if (fabs(rate - pre) < EPS) {
            break;
        }
    }

    printf("%.10f\n", rate);
    return 0;
}
