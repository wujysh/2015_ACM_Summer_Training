#include <iostream>
#include <cstdio>
using namespace std;

const int m[3] = {23, 28, 33};

int p, e, i, d, cCase, x;

int extend_gcd(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    } else {
        int r = extend_gcd(b, a%b, y, x);
        y -= x * (a/b);
        return r;
    }
}

int CRT(int a[], const int m[], int n) {
    int M = 1;
    for (int i = 0; i < n; i++) {
        M *= m[i];
    }
    int ret = 0;
    for (int i = 0; i < n; i++) {
        int x, y;
        int tm = M / m[i];
        extend_gcd(tm, m[i], x, y);
        ret = (ret + tm * x * a[i]) % M;
    }
    return (ret + M) % M;
}

int main() {
    while (~scanf("%d%d%d%d", &p, &e, &i, &d) && (~p || ~e || ~i || ~d)) {
        //x = (5544*p + 14421*e + 1288*i - d + 21252) % 21252;
        //if (x == 0) {
        //    x = 21252;
        //}
        int a[3] = {p, e, i};
        x = CRT(a, m, 3) - d;
        if (x <= 0) {
            x += 21252;
        }
        printf("Case %d: the next triple peak occurs in %d days.\n", ++cCase, x);
    }
    return 0;
}
