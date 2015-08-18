#include <iostream>
#include <cstdio>
using namespace std;

const int MAXN = 30;

int n, a[MAXN];

int main() {
    while (scanf("%d", &n) && n) {
        a[0] = 0;
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
        }
        int isfirst = true;
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < a[i] - a[i - 1]; j++) {
                if (!isfirst) {
                    printf(" ");
                }
                printf("%d", i);
                isfirst = false;
            }
        }
        printf("\n");
    }
    return 0;
}
