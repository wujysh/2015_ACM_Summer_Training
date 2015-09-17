#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
using namespace std;

const int MAXN = 1010;
const int MAXM = 5010;

int n, m, p, l[MAXN], c[MAXM][MAXM], dp[MAXN][MAXM];

void init() {
    memset(c, 0, sizeof(c));
    c[0][0] = 1;
    for (int i = 1; i <= 5000; i++) {
        c[i][0] = 1;
        for (int j = 1; j <= 5000; j++) {
            c[i][j] = (c[i-1][j] + c[i-1][j-1]) % p;
        }
    }
}

int C(int n, int m) {
    return c[n][m];
}

int main() {
    scanf("%d%d%d", &n, &m, &p);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &l[i]);
    }

    init();

    for (int i = 1; i <= m; i++) {
        dp[0][i] = 1;
    }
    l[0] = l[1];

    for (int i = 1; i <= min(l[1], m); i++) {
        dp[1][i] = ((C(m, i) * i) % p * (int)pow(i-1, l[1]-1)) % p;
    }

    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= min(l[i], m); j++) {
            for (int k = 1; k <= min(l[i-1], m); k++) {
                if (j != k) {
                    dp[i][j] = (dp[i][j] + (((dp[i-1][k] * C(m, j)) % p * j) % p * (int)pow(j-1, l[i]-1)) % p) % p;
                    //cout << i << " " << j << " " << k << " " << dp[i][j] << endl;
                } else {
                    dp[i][j] = (dp[i][j] + (((dp[i-1][k] * (C(m, j)-1)) % p * j) % p * (int)pow(j-1, l[i]-1)) % p) % p;
                }
            }
        }
    }

    int ans = 0;
    for (int i = 1; i <= m; i++) {
        ans = (ans + dp[n][i]) % p;
    }

    printf("%d\n", ans);

    return 0;
}
