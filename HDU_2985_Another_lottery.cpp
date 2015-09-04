#include <iostream>
#include <cstdio>
using namespace std;

const int MAXN = 10010;
const int MAXM = 35;

int n, m, a[MAXN][MAXM];

long long sum;

void init() {
    sum = 0;
}

void input() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &a[i][j]);
        }
    }
}

int gcd(int a, int b) {
    return b > 0 ? gcd(b, a % b) : a;
}

void solve() {
    for (int i = 0; i < n; i++) {
        sum += a[i][m - 1];
    }

    for (int i = 0; i < n; i++) {
        if (a[i][m - 1] == 0) {
            printf("%lld / %lld\n", 0, 1);
        } else {
            long long t = gcd(a[i][m - 1], sum);
            printf("%lld / %lld\n", a[i][m - 1] / t, sum / t);
        }
    }
}

int main() {
    while (~scanf("%d%d", &n, &m) && (n || m)) {
        init();
        input();
        solve();
    }
    return 0;
}
