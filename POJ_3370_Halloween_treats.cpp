#include <iostream>
#include <cstdio>
using namespace std;

const int MAXN = 100010;

int n, c, a[MAXN], sum[MAXN], pos[MAXN];

void init() {
    sum[0] = 0;
    for (int i = 0; i <= c; i++) {
        pos[i] = -1;
    }
}

void input() {
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
}

void print(int l, int r) {
    printf("%d", l);
    for (int i = l+1; i <= r; i++) {
        printf(" %d", i);
    }
    printf("\n");
}

void solve() {
    for (int i = 1; i <= n; i++) {
        sum[i] = (sum[i-1] + a[i]) % c;
        if (sum[i] == 0) {
            print(1, i);
            break;
        } else if (pos[sum[i]] != -1) {
            print(pos[sum[i]]+1, i);
            break;
        }
        pos[sum[i]] = i;
    }
}

int main() {
    while (~scanf("%d%d", &c, &n) && (c || n)) {
        init();
        input();
        solve();
    }
    return 0;
}
