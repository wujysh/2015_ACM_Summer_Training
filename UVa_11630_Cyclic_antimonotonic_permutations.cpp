#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
using namespace std;

const int MAXN = 1000010;

int n, a[MAXN], pos[MAXN];

void init() {
    memset(a, 0, sizeof(a));
    memset(pos, 0, sizeof(pos));
}

void solve() {
    a[1] = 1;
    pos[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (i % 2 == 1) {  // odd
            a[pos[(i+1) / 2]] = i;
            pos[i] = pos[(i + 1) / 2];
            a[i] = (i + 1) / 2;
            pos[(i + 1) / 2] = i;
        } else {  // even
            a[pos[i / 2]] = i;
            pos[i] = pos[i / 2];
            a[i] = i / 2;
            pos[i / 2] = i;
        }
    }

    for (int i = 1; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("%d\n", a[n]);
}

int main() {
    while (~scanf("%d", &n) && n) {
        init();
        solve();
    }
    return 0;
}
