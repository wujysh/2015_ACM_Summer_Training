#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

const int MAXN = 55;
const int MAXM = 100100;
const int INF = 0x3f3f3f3f;

int n, m, nCase, z[MAXN][MAXN];

/// KM
int link[MAXM], w[MAXN][MAXM];
int lx[MAXM], ly[MAXM];
int slack[MAXM];
bool vtx[MAXM], vty[MAXM], vt[MAXM];
int match[MAXM];

bool dfs(int i) {
    int j;
    vtx[i] = true;

    for (j = 1; j <= m; j++) {
        if (vty[j]) continue;
        int tmp = lx[i] + ly[j] - w[i][j];
        if (tmp == 0) {
            vty[j] = true;
            if (dfs(link[j]) || link[j] == -1) {
                link[j] = i;
                return true;
            }
        } else {
            slack[j] = min(tmp, slack[j]);
        }
    }
    return false;
}

int KM() {
    for (int i = 1; i <= n; i++) {
        lx[i] = -INF;
        for (int j = 1 ; j <= m; j++) {
            lx[i] = max(lx[i], w[i][j]);
        }
    }
    memset(link , -1 , sizeof(link));
    memset(ly , 0 , sizeof(ly));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            slack[j] = INF;
        }
        while (true) {
            memset(vtx , false , sizeof(vtx));
            memset(vty , false , sizeof(vty));
            if (dfs(i)) {
                break;
            }
            int d = INF;
            for (int j = 1; j <= m; j++) {
                if (!vty[j] && d > slack[j])
                    d = slack[j];
            }
            if (d == INF) return -1;
            for (int j = 1; j <= n; j++) {
                if (vtx[j]) {
                    lx[j] -= d;
                }
            }
            for (int j = 1; j <= m; j++) {
                if (vty[j]) {
                    ly[j] += d;
                } else {
                    slack[j] -= d;
                }
            }

        }
    }
    int sum = 0;
    for (int i = 1; i <= m; i++) {
        if (link[i] > -1)
            sum -= w[link[i]][i];
    }
    return sum;
}

void init() {
    memset(w, 0, sizeof(w));
}

void input() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", &z[i][j]);
        }
    }
}

void solve() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            for (int k = 1; k <= n; k++) {
                w[i][(j-1)*n+k] = -z[i][j] * k;
            }
        }
    }
    m = n * m;
    printf("%.6f\n", (double)KM() / n);
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
