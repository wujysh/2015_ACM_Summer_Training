#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
using namespace std;

const int MAXN = 20;
const int INF = 0x3f3f3f3f;

int m, n, minStep;
bool flag, ans[MAXN][MAXN], flip[MAXN][MAXN], a[MAXN][MAXN], b[MAXN][MAXN];

void init() {
    flag = false;
    minStep = INF;
}

void input() {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &a[i][j]);
        }
    }
}

int judge(int state) {
    int cnt = 0;

    for (int i = 0; i < n; i++) {  // line 1
        if (state & (1 << i)) {
            flip[0][i] = true;
            cnt++;
            b[0][i] = !b[0][i];
            if (i + 1 < n) {
                b[0][i+1] = !b[0][i+1];
            }
            if (i - 1 >= 0) {
                b[0][i-1] = !b[0][i-1];
            }
            if (2 <= m) {
                b[1][i] = !b[1][i];
            }
        }
    }

    for (int i = 1; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (b[i-1][j]) {
                flip[i][j] = true;
                cnt++;
                b[i][j] = !b[i][j];
                if (j + 1 < n) {
                    b[i][j+1] = !b[i][j+1];
                }
                if (j - 1 >= 0) {
                    b[i][j-1] = !b[i][j-1];
                }
                if (i + 1 < m) {
                    b[i+1][j] = !b[i+1][j];
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (b[m-1][i]) {
            return INF;
        }
    }
    return cnt;
}

void solve() {
    for (int i = 0; i < (1 << n); i++) {
        memset(flip, false, sizeof(flip));
        memcpy(b, a, sizeof(a));
        int step = judge(i);
        if (step != INF) {
            flag = true;
            if (step < minStep) {
                minStep = step;
                memcpy(ans, flip, sizeof(flip));
            }
        }
    }

    if (flag) {
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n-1; j++) {
                printf("%d ", ans[i][j]);
            }
            printf("%d\n", ans[i][n-1]);
        }
    } else {
        printf("IMPOSSIBLE\n");
    }
}

int main() {
    while (~scanf("%d%d", &m, &n)) {
        init();
        input();
        solve();
    }
    return 0;
}
