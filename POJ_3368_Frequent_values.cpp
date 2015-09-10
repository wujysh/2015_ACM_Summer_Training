#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

const int MAXN = 100010;

int n, q, a[MAXN], f[MAXN], MAX[MAXN][20];

void input() {
    scanf("%d", &q);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
}

void ST() {
    for (int i = 1; i <= n; i++) {
        MAX[i][0] = f[i];
    }
    int k = log2(n + 1);
    for (int j = 1; j <= k; j++) {
        for (int i = 1; i + (1 << j) - 1 <= n; i++) {
            MAX[i][j] = max(MAX[i][j - 1], MAX[i + (1 << (j - 1))][j - 1]);
        }
    }
}

int rmq_max(int l, int r) {
    if (l > r) return 0;
    int k = log2(r - l + 1);
    return max(MAX[l][k], MAX[r - (1 << k) + 1][k]);
}

void solve() {
    f[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (a[i] == a[i - 1]) {
            f[i] = f[i - 1] + 1;
        } else {
            f[i] = 1;
        }
    }

    ST();

    while (q--) {
        int i, j;
        scanf("%d%d", &i, &j);
        int t = i;
        while (t <= j && a[t] == a[t - 1]) {
            t++;
        }
        printf("%d\n", max(t - i, rmq_max(t, j)));
    }
}

int main() {
    while (~scanf("%d", &n) && n) {
        input();
        solve();
    }
    return 0;
}
