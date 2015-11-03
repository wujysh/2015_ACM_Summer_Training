#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

const int MOD = 9973;

int n, ans, a[MOD + 10], b[MOD + 10];

void init() {
    a[0] = 1;
    for (int i = 1; i <= MOD; i++) {
        int x1 = i, x3 = x1 * i % MOD * i % MOD, x5 = x3 * i % MOD * i % MOD;
        a[i] = (x5 - x1 + 7 + MOD) % MOD;
        b[i] = (x3 - x5 + 3 * x1 + MOD) % MOD;
        b[i] = (a[i] * b[i-1] % MOD + b[i]) % MOD;
        a[i] = a[i] * a[i-1] % MOD;
    }
}

int main() {
    init();
    while (~scanf("%d", &n)) {
        ans = 0;
        for (int i = n / MOD; i > 0; i--) {
            ans = (ans * a[MOD] % MOD + b[MOD]) % MOD;
        }
        ans = (ans * a[n % MOD] % MOD + b[n % MOD]) % MOD;

        printf("%d\n", ans);
    }
    return 0;
}
