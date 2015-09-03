#include <iostream>
#include <cstdio>
using namespace std;

const double L = 1.6180339887;

int main() {
    long long a, b, det;
    while (~scanf("%lld %lld", &a, &b)) {
        if (a > b) {
            a ^= b ^= a ^= b;
        }
        det = b - a;
        if (a == int(det * L)) {
            printf("0\n");
        } else {
            printf("1\n");
        }
    }
    return 0;
}
