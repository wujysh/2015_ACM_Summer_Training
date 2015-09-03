#include <iostream>
#include <cstdio>
using namespace std;

const int MAXN = 1010;
const int MOD = 1000000007;

long long C[MAXN][MAXN];

int k, c[MAXN];

void init() {
    C[0][0] = 1;
    for (int i = 1; i < MAXN; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            C[i][j] = (C[i-1][j] + C[i-1][j-1]) % MOD;
        }
    }
}

int main() {
    init();

    scanf("%d", &k);
    for (int i = 0; i < k; i++) {
        scanf("%d", &c[i]);
    }

    long long ans = 1, t = 0;
    for (int i = 0; i < k; i++) {
        ans = (ans * C[t + c[i] - 1][c[i] - 1]) % MOD;
        t += c[i];
    }

    printf("%I64d\n", ans);

    return 0;
}
