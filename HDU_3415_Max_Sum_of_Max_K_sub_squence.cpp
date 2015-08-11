#include <iostream>
#include <cstdio>
using namespace std;

const int MAXN = 200010;
const int INF = 0x3f3f3f3f;
int n, k, nCase, sum[MAXN], a[MAXN], q[MAXN], l, r;

void init() {
    sum[0] = 0;
    l = r = 0;
}

void input() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        a[i+n] = a[i];
    }
    for (int i = 1; i <= 2*n; i++) {
        sum[i] = sum[i-1] + a[i];
    }
}

void solve() {
    q[r++] = 0;
    int starti = 0, endi = 0, ans = -INF;
    for (int i = 1; i <= 2*n; i++) {
        while (l < r && i-q[l] > k) l++;
        if (sum[i] - sum[q[l]] > ans) {
            ans = sum[i] - sum[q[l]];
            starti = q[l] + 1;
            endi = i > n ? i-n : i;
        }
        while (l < r && sum[q[r-1]] > sum[i]) r--;
        q[r++] = i;
    }

    printf("%d %d %d\n", ans, starti, endi);
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
