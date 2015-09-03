#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

const int MAXN = 15;
const int MOD = 1000000007;

int dp[MAXN][MAXN], digit[MAXN], len, m, cnt[MAXN];

int DP(int n, int cnt, bool limit) {
    if (cnt < 0) {
        return 0;
    }
    if (n == 0) {
        if (cnt == 0) {
            return 1;
        } else {
            return 0;
        }
    }
    if (!limit && dp[n][cnt] != -1) {
        return dp[n][cnt];
    }

    int ans = 0, maxDigit = limit ? digit[n] : 9;
    for (int i = 0; i <= maxDigit; i++) {
        ans = (ans + DP(n-1, cnt - (i == 4 || i == 7), limit && i == digit[n])) % MOD;
    }

    if (!limit) dp[n][cnt] = ans;
    return ans;
}

void init() {
    memset(dp, -1, sizeof(dp));
}

void solve(int x) {
    len = 0;
    while (x) {
        digit[++len] = x % 10;
        x /= 10;
    }

    for (int i = 0; i <= len; i++) {
        cnt[i] = DP(len, i, true) % MOD;
    }
    cnt[0]--;  // exclude 0
}

long long calc(int a, int b) {
    if (b > a) return 0;
    long long ret = 1;
    for (int i = a; i >= a-b+1; i--) {
        ret = (ret * i) % MOD;
    }
    return ret;
}

long long dfs(int now, int d[], int sum) {
    if (sum >= d[0]) return 0;
    if (now == 7) {
        int t[MAXN] = {0};
        for (int i = 0; i < 7; i++) {
            t[d[i]]++;
        }
        long long ret = 1;
        for (int i = 0; i <= len; i++) {
            ret = (ret * calc(cnt[i], t[i])) % MOD;
        }
        return ret;
    }

    long long ret = 0;
    for (int i = 0; i <= len; i++) {
        d[now] = i;
        ret = (ret + dfs(now+1, d, sum+i)) % MOD;
    }
    return ret;
}

int main() {
    init();

    while (~scanf("%d", &m)) {
        solve(m);

        long long ans = 0;
        for (int i = 0; i <= len; i++) {
            //cout << i << " " << cnt[i] << endl;
            if (cnt[i]) {
                int d[MAXN] = {0};
                d[0] = i;
                ans = (ans + dfs(1, d, 0)) % MOD;
            }
        }

        printf("%I64d\n", ans);
    }

    return 0;
}
