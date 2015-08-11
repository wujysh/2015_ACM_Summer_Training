#include <iostream>
#include <cstdio>
using namespace std;

int n, k;

int main() {
    scanf("%d%d", &n, &k);

    if (n*(n-1) > 2*k) {
        for (int i = 0; i < n; i++) {
            printf("%d %d\n", 0, i);
        }
    } else {
        printf("no solution\n");
    }

    return 0;
}
