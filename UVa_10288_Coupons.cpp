#include <algorithm>
#include <iostream>
#include <cstdio>
using namespace std;

long long n, fz, fm, num;

void reduce(long long &fz, long long &fm, long long &num) {
    if (fz >= fm) {
        num += fz / fm;
        fz %= fm;
    }
    long long t = __gcd(fz, fm);
    if (t > 1) {
        fz /= t;
        fm /= t;
    }
}

void solve() {
    fz = 1, fm = 1, num = 0;
    for (int i = 2; i <= n; i++) {
        long long a = fm, b = i;
        fm = a / __gcd(a, b) * b;
        fz = fm / a * fz + fm / b;
        reduce(fz, fm, num);
    }
    fz *= n;
    num *= n;
    reduce(fz, fm, num);
}

int calcLen(long long num) {
    int cnt = 0;
    while (num > 0) {
        cnt++;
        num /= 10;
    }
    return cnt;
}

void print() {
    if (fz == 0) {
        printf("%lld\n", num);
    } else {
        int lenFraction = max(calcLen(fz), calcLen(fm));
        int lenInteger = calcLen(num);

        for (int i = 0; i <= lenInteger; i++) {
            printf(" ");
        }
        printf("%lld\n", fz);

        printf("%lld ", num);
        for (int i = 0; i < lenFraction; i++) {
            printf("-");
        }
        printf("\n");

        for (int i = 0; i <= lenInteger; i++) {
            printf(" ");
        }
        printf("%lld\n", fm);
    }
}

int main() {
    while (~scanf("%lld", &n)) {
        solve();
        print();
    }
    return 0;
}
