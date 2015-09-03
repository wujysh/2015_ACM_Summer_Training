#include <iostream>
#include <cstdio>
using namespace std;

const int INF = 0x3f3f3f3f;
const int MOD = 1000000007;
const int MAXN = 1000010;

long long f[MAXN], a, b, n;

bool isExcellent(int x) {
    while (x) {
        if (x % 10 != a && x % 10 != b) {
            return false;
        }
        x /= 10;
    }
    return true;
}

long long pow_mod(long long a, long long b, int p) {
    long long ret = 1, t = a;
    while (b) {
        if (b & 1) {
            ret = (ret * t) % p;
        }
        t = (t * t) % p;
        b = b >> 1;
    }
    return ret;
}

void init() {
    f[0] = f[1] = 1;
    for (int i = 2; i < MAXN; i++) {
        f[i] = (f[i-1] * i) % MOD;
    }
}

int main() {
    init();
    while (~scanf("%I64d%I64d%I64d", &a, &b, &n)) {
        long long ans = 0;
        for (int i = 0; i <= n; i++) {
            int num = a * i + b * (n-i);
            if (isExcellent(num)) {
                long long t = f[n];
                t = (t * pow_mod(f[i], MOD-2, MOD)) % MOD;
                t = (t * pow_mod(f[n-i], MOD-2, MOD)) % MOD;
                ans = (ans + t) % MOD;
            }
        }
        printf("%I64d\n", ans);
    }
    return 0;
}
