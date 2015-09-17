#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
using namespace std;

const int MAXP = 20;
const int MAXN = 100010;

int nCase;
long long n, m, k, p[MAXP], fac[MAXN];

void getfac(long long p) {
    fac[0] = 1;
    for (int i = 1; i <= p; i++) {
        fac[i] = fac[i - 1] * i % p;
    }
}

long long pow_mod(long long a, long long n, long long p) {
    long long ans = 1;
    while (n) {
        if (n & 1) {
            ans = ans * a % p;
        }
        a = a * a % p;
        n /= 2;
    }
    return ans;
}

long long lucas(long long n, long long m, long long p) {
    long long ans = 1;
    while (n && m) {
        long long a = n % p;
        long long b = m % p;
        if (a < b) return 0;
        ans = ((ans * fac[a]) % p * pow_mod(fac[b] * fac[a - b] % p, p - 2, p)) % p;
        n /= p;
        m /= p;
    }
    return ans;
}

long long extend_gcd(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    long long gcdans = extend_gcd(b, a % b, x, y);
    long long temp = x;
    x = y;
    y = temp - (a / b) * y;
    return gcdans;
}

void input() {
    scanf("%I64d%I64d%I64d", &n, &m, &k);
    for (int i = 0; i < k; i++) {
        scanf("%I64d", &p[i]);
    }
}

void solve() {
    getfac(p[0]);
    long long t = lucas(n, m, p[0]);
    long long a = p[0];
    for (int i = 1; i < k; i++) {
        getfac(p[i]);
        long long t1 = lucas(n, m, p[i]);

        long long x, y;
        extend_gcd(a, p[i], x, y);
        x *= t1 - t;
        x = (x % p[i] + p[i]) % p[i];

        t += a * x;
        a = a * p[i];
    }

    printf("%I64d\n", t);
}

int main() {
    scanf("%d", &nCase);
    while (nCase--) {
        input();
        solve();
    }
    return 0;
}
