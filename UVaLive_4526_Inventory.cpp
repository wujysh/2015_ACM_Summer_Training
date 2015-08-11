#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int INF = 0x3f3f3f3f;
const int MAXN = 1010;
int dp[1010][110];
int ans, n, nCase, a[MAXN], b[MAXN], c[MAXN];

void init() {
    memset(dp, 0x3f, sizeof(dp));
}

void input() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d%d%d", &a[i], &b[i], &c[i]);
    }
}

void solve() {//a-price, b-max, c-order
    dp[0][c[0]] = c[0] * a[0];
    for (int i = 1; i < n; i++) {
        for (int j = 0; j <= min(b[i], c[i]); j++) {
            for (int k = 0; k <= min(b[i-1], c[i-1]) && k + c[i]-j <= b[i-1]; k++) {
                if (dp[i-1][k] != INF) {
                    //cout << i << " "  << j << " " << k << endl;
                    dp[i][j] = min(dp[i][j], j * a[i] + (c[i]-j)*a[i-1] + dp[i-1][k]);
                }
            }
        }
    }
    int ans = INF;
    //cout << "+++" << dp[1][0] << " " << dp[1][1] << endl;
    for (int i = 0; i <= c[n-1]; i++) {
        if (dp[n-1][i] != INF) {
            ans = min(ans, dp[n-1][i]);
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
