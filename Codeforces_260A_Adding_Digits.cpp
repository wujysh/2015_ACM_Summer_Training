#include <iostream>
#include <cstdio>
#include <string>

long long a, b, n;

int main() {
    scanf("%I64d%I64d%I64d", &a, &b, &n);
    bool possible = false;
    a *= 10;
    for (int k = 0; k < 10; k++) {
        if ((a + k) % b == 0) {
            a += k;
            possible = true;
            break;
        }
    }
    if (possible) {
        printf("%I64d", a);
        while (--n) {
            printf("0");
        }
        printf("\n");
    } else {
        puts("-1");
    }
    return 0;
}
