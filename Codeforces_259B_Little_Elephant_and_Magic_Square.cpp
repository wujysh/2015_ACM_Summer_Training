#include <iostream>
#include <cstdio>
using namespace std;

const int MAXN = 10;

int a[MAXN][MAXN];

int main() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            scanf("%d", &a[i][j]);
        }
    }
    for (int i = 1; i <= 100000; i++) {
        int sum = i + a[0][1] + a[0][2];
        int j = sum - a[0][1] - a[2][1];
        if (j > 0 && j == sum - a[1][0] - a[1][2]) {
            int k = sum - a[0][2] - a[1][2];
            if (k > 0 && k == sum - a[2][0] - a[2][1]) {
                if (i + j + k == sum) {
                    printf("%d %d %d\n", i, a[0][1], a[0][2]);
                    printf("%d %d %d\n", a[1][0], j, a[1][2]);
                    printf("%d %d %d\n", a[2][0], a[2][1], k);
                    break;
                }
            }
        }
    }
    return 0;
}
