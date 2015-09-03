#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

const int MAXN = 100010;

int n, m;
long long y[MAXN], z[MAXN];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int v;
        scanf("%d", &v);
        y[i] = z[i] = v;
    }

    sort(y + 1, y + n + 1);

    for (int i = 1; i <= n; i++) {
        z[i] += z[i - 1];
        y[i] += y[i - 1];
    }

    scanf("%d", &m);
    for (int i = 1; i <= m; i++) {
        int op, l, r;
        scanf("%d%d%d", &op, &l, &r);
        if (op == 1) {
            printf("%I64d\n", z[r] - z[l - 1]);
        } else {
            printf("%I64d\n", y[r] - y[l - 1]);
        }
    }

    return 0;
}
