#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

const int MAXN = 100010;
const int MAXM = 20;

int nCase, n, k, a[MAXN], rmq_max[MAXN][MAXM], rmq_min[MAXN][MAXM];
long long ans;

void init() {
    ans = 0;
}

void input() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
}

void rmq_init() {
    for (int i = 1; i <= n; i++) {
        rmq_max[i][0] = rmq_min[i][0] = a[i];
    }
    for (int j = 1; j < MAXM; j++) {
        for (int i = 1; i <= n; i++) {
            if (i + (1 << j) - 1 <= n) {
                rmq_max[i][j] = max(rmq_max[i][j - 1], rmq_max[i + (1 << (j - 1))][j - 1]);
                rmq_min[i][j] = min(rmq_min[i][j - 1], rmq_min[i + (1 << (j - 1))][j - 1]);
            }
        }
    }
}

pair<int, int> rmq_query(int l, int r) {  // return <max, min>
    int k = floor(log2((double)(r - l + 1)));
    return make_pair(max(rmq_max[l][k], rmq_max[r - (1 << k) + 1][k]), min(rmq_min[l][k], rmq_min[r - (1 << k) + 1][k]));
}

void solve() {
    rmq_init();

    for (int i = 1; i <= n; i++) {
        int l = i, r = n;
        while (l <= r) {
            int mid = (l + r) >> 1;
            pair<int, int> rmq = rmq_query(i, mid);
            if (rmq.first - rmq.second >= k) {
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        ans += r - i + 1;
    }

    printf("%lld\n", ans);
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
