#include <algorithm>
#include <iostream>
#include <cstdio>
using namespace std;

const int MAXN = 5010;

int l[MAXN], r[MAXN], a[MAXN << 1], father[MAXN << 2], len, n;
char str[MAXN][6];

int find_set(int x) {
    return father[x] == x ? x : father[x] = find_set(father[x]);
}

void init() {
    for (int i = 0; i < (MAXN << 2); i++) {
        father[i] = i;
    }
}

void input() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d%d%s", &l[i], &r[i], str[i]);
        a[i << 1] = l[i];
        a[i << 1 | 1] = r[i];
    }
}

void solve() {
    sort(a, a + n * 2);
    int new_len = unique(a, a + n * 2) - a;
    a[++new_len] = 1e9 + 7;

    for (int i = 0; i < n; i++) {
        if (l[i] < 0 || r[i] > len) {
            printf("%d\n", i);
            return;
        }

        int ll = lower_bound(a, a + new_len, l[i]) - a + 1;
        int rr = lower_bound(a, a + new_len, r[i]) - a + 1;

        int lp = find_set(ll - 1), rp = find_set(rr);
        int llp = find_set(ll - 1 + new_len), rrp = find_set(rr + new_len);

        if (str[i][0] == 'e') {
            if (rp == llp || rrp == lp) {
                printf("%d\n", i);
                return;
            }
            if (rp != lp) {
                father[rp] = lp;
            }
            if (rrp != llp) {
                father[rrp] = llp;
            }
        } else if (str[i][0] == 'o') {
            if (rp == lp || rrp == llp) {
                printf("%d\n", i);
                return;
            }
            if (rp != llp) {
                father[rp] = llp;
            }
            if (rrp != lp) {
                father[rrp] = lp;
            }
        }
    }

    printf("%d\n", n);
}

int main() {
    while (~scanf("%d", &len) && len != -1) {
        init();
        input();
        solve();
    }
    return 0;
}
