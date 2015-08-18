#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

const int MAXN = 30010;
int n, g, cntX[MAXN], cntY[MAXN], cntXY[2 * MAXN], cntYX[2 * MAXN], ans;

int main() {
    while (~scanf("%d", &n) && n) {
        scanf("%d", &g);

        memset(cntX, 0, sizeof(cntX));
        memset(cntY, 0, sizeof(cntY));
        memset(cntXY, 0, sizeof(cntXY));
        memset(cntYX, 0, sizeof(cntYX));
        ans = 0;

        for (int i = 0; i < g; i++) {
            int kk, x, y, s, t;
            scanf("%d%d%d%d%d", &kk, &x, &y, &s, &t);

            for (int k = 0; k < kk; k++) {
                int xx = x + k * s, yy = y + k * t;
                cntX[xx]++;
                cntY[yy]++;
                cntXY[xx + yy]++;
                cntYX[xx - yy + n]++;
            }
        }

        for (int i = 1; i <= n; i++) {
            if (cntX[i])
                ans += cntX[i] - 1;
            if (cntY[i]) ans += cntY[i] - 1;
        }
        for (int i = 1; i <= 2 * n; i++) {
            if (cntXY[i]) ans += cntXY[i] - 1;
            if (cntYX[i]) ans += cntYX[i] - 1;
        }

        printf("%d\n", ans);
    }
    return 0;
}
