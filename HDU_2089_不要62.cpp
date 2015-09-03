#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

const int MAXN = 7;

int dp[MAXN][2], n, m, digit[MAXN], len;

int DP(int n, bool flag, bool limit) {
    if (n == 0) return 1;
    if (!limit && dp[n][flag] != -1) return dp[n][flag];

    int ans = 0, maxDigit = limit ? digit[n] : 9;
    for (int i = 0; i <= maxDigit; i++) {
        if (i == 4 || (flag && i == 2)) continue;
        ans += DP(n-1, i == 6, limit && i == digit[n]);
    }

    if (!limit) dp[n][flag] = ans;
    return ans;
}

void init() {
    memset(dp, -1, sizeof(dp));
}

int solve(int x) {
    len = 0;
    while (x) {
        digit[++len] = x % 10;
        x /= 10;
    }
    return DP(len, false, true);
}

int main() {
    init();
    while (~scanf("%d%d", &n, &m) && (n || m)) {
        printf("%d\n", solve(m) - solve(n-1));
    }
    return 0;
}
