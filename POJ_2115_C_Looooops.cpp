#include <iostream>
#include <cstdio>
using namespace std;

long long a, b, c, k;

long long extend_gcd(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    } else {
        long long r = extend_gcd(b, a % b, y, x);
        y -= x * (a / b);
        return r;
    }
}

int main() {
    while (~scanf("%lld%lld%lld%lld", &a, &b, &c, &k) && (a || b || c || k)) {
        long long n = ((long long)(1) << k);
        long long x, y;
        long long d = extend_gcd(c, n, x, y);

        if ((a - b) % d != 0) {
            printf("FOREVER\n");
        } else {
            x = (x * ((b - a) / d)) % n;
            while (x < 0) {
                x += n / d;
            }
            while (x - n / d > 0) {
                x -= n / d;
            }
            printf("%lld\n", x);
        }
    }
    return 0;
}
