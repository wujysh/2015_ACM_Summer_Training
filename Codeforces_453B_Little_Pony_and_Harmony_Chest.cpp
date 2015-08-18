#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
using namespace std;

const int MAXN = 110;
const int MAXP = 16;
const int PRIME[MAXP] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53};
const int INF = 0x3f3f3f3f;

int n, a[MAXN], b[MAXN], fact[MAXN], dp[MAXN][(1 << MAXP) + 10], rec[MAXN][(1 << MAXP) + 10];

int getFact(int a) {
    int fact = 0;
    for (int i = 0; i < MAXP; i++) {
        while (a % PRIME[i] == 0) {
            a /= PRIME[i];
            fact |= (1 << i);
        }
    }
    return fact;
}

void generateAns(int deep, int state) {
    if (deep == 0) {
        return;
    }

    int u = rec[deep][state];
    generateAns(deep - 1, state ^ fact[u]);
    b[deep] = u;
}

void init() {
    for (int i = 1; i < 60; i++) {
        fact[i] = getFact(i);
    }
}

void input() {
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
}

void solve() {
    memset(rec, -1, sizeof(rec));
    rec[0][0] = 0;

    for (int i = 0; i < n; i++) {
        for (int s = 0; s < (1 << MAXP); s++) {
            if (rec[i][s] == -1) continue;

            for (int k = 1; k < 60; k++) {
                if (s & fact[k]) continue;

                int ns = s | fact[k];
                if (rec[i + 1][ns] == -1 || dp[i][s] + abs(a[i + 1] - k) < dp[i + 1][ns]) {
                    rec[i + 1][ns] = k;
                    dp[i + 1][ns] = dp[i][s] + abs(a[i + 1] - k);
                }
            }
        }
    }

    int ans = INF, state;
    for (int i = 0; i < (1 << MAXP); i++) {
        if (dp[n][i] < ans && rec[n][i] != -1) {
            ans = dp[n][i];
            state = i;
        }
    }

    generateAns(n, state);
    for (int i = 1; i < n; i++) {
        printf("%d ", b[i]);
    }
    printf("%d\n", b[n]);
}

int main() {
    init();
    while (~scanf("%d", &n)) {
        input();
        solve();
    }
    return 0;
}
