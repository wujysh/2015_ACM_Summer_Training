#include <iostream>
#include <cstdio>
using namespace std;

int n, m, x, y, a, b, d, t;

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    scanf("%d%d%d%d%d%d", &n, &m, &x, &y, &a, &b);

    d = gcd(a, b);
    a /= d;
    b /= d;
    t = min(n/a, m/b);
    a *= t;
    b *= t;

    int xx = x, yy = y;
    while (true) {
        if (xx + a/2 > n) {
            xx--;
        } else if (xx - a/2 - a%2 < 0) {
            xx++;
        } else if (yy + b/2 > m) {
            yy--;
        } else if (yy - b/2 - b%2 < 0) {
            yy++;
        } else {
            printf("%d %d %d %d\n", xx-a/2-a%2, yy-b/2-b%2, xx+a/2, yy+b/2);
            break;
        }
    }

    return 0;
}
