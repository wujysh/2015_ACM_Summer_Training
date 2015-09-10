#include <algorithm>
#include <iostream>
#include <cstdio>
using namespace std;

const int MAXN = 1010;
int nCase, n, a[MAXN];

int main() {
    scanf("%d", &nCase);
    while (nCase--) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
        }
        sort(a, a+n);
        for (int i = 0; i < n; i++) {
            if (i) printf(" ");
            printf("%d", a[i]);
        }
        printf("\n");
    }
    return 0;
}
