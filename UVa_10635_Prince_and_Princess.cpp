#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

const int MAXN = 62510;

int n, p, q, cnt, nCase, cCase, a[MAXN], b[MAXN], save[MAXN];

void init() {
    memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));
    memset(save, 0, sizeof(save));
    cnt = 1;
}

void input() {
    scanf("%d%d%d", &n, &p, &q);
    int x;
    for (int i = 1; i <= p+1; i++) {
        scanf("%d", &x);
        a[x] = i;
    }
    for (int i = 1; i <= q+1; i++) {
        scanf("%d", &x);
        if (a[x]) {
            b[cnt++] = a[x];
        }
    }
}

int bsearch(int l, int r, int key) {
    while (l < r) {
        int mid = (l + r) >> 1;
        if (save[mid] > key) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    return r;
}

void solve() {
    save[1] = b[1];
    int j = 1, mid;
    for (int i = 2; i < cnt; i++) {
        if (b[i] > save[j]) {
            save[++j] = b[i];
        } else {
            mid = bsearch(1, j, b[i]);
            save[mid] = b[i];
        }
    }

    if (cnt == 1) {
        j = 0;
    }
    printf("Case %d: %d\n", ++cCase, j);
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
