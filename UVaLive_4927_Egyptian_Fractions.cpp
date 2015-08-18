#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

long long m, n;

long long gcd(long long a, long long b) {
    if (a < b) swap(a, b);
    return b == 0 ? a : gcd(b, a % b);
}

long long lcm(long long a, long long b) {
    return a / gcd(a, b) * b;
}

bool judge(long long m, long long n, long long k) {
    long long fm = lcm(n, k);
    long long fz = fm / n * m - fm / k;
    if (fz > 0) {
        long long x = gcd(fz, fm);
        fz /= x;
        fm /= x;
    }
    if (fz >= 0 && fm < 1000000) return true;
    else return false;
}

void sub(long long &m, long long &n, long long k) {
    long long fm = lcm(n, k);
    long long fz = fm / n * m - fm / k;
    if (fz > 0) {
        long long x = gcd(fz, fm);
        fz /= x;
        fm /= x;
    }
    m = fz;
    n = fm;
}

int main() {
    while (~scanf("%lld%lld", &m, &n) && (m || n)) {
        bool first = true;
        while (true) {
            long long k;
            for (k = ceil(n / m); k < 1000000; k++) {
                if (judge(m, n, k)) {
                    break;
                }
            }
            if (!first) printf(" ");
            first = false;
            printf("%lld", k);
            sub(m, n, k);
            if (m == 0) break;
        }
        printf("\n");
    }
    return 0;
}
