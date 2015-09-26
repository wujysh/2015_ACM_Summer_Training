#include <algorithm>
#include <iostream>
#include <cstdio>
using namespace std;

const int MAXN = 110;

int nCase, cCase, n, A, B, L;

struct Node {
    int l, r;
    bool operator <(const Node &b) const {
        return l < b.l;
    }
} a[MAXN];

bool judge(int x) {
    x += a[0].l * B;
    for (int i = 0; i < n; i++) {
        if (x < 0) return false;
        if (i > 0) {
            x += (a[i].l - a[i-1].r) * B;
        }
        x -= (a[i].r - a[i].l) * A;
    }
    if (x < 0) return false;
    return true;
}

int main() {
    scanf("%d", &nCase);
    while (nCase--) {
        scanf("%d%d%d%d", &n, &A, &B, &L);
        for (int i = 0; i < n; i++) {
            scanf("%d%d", &a[i].l, &a[i].r);
        }

        sort(a, a + n);

        int l = 0, r = L * A;
        while (l < r) {
            int mid = (l + r) >> 1;

            if (judge(mid)) {
                r = mid;
            } else {
                l = mid + 1;
            }
        }

        printf("Case #%d: %d\n", ++cCase, l);
    }
    return 0;
}
