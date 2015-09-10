#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;

const int MAXN = 1010;
int n, m, k[MAXN], sum[MAXN], q, d;

int main() {
    while (~scanf("%d%d", &n, &m)) {
        sum[0] = 0;
        for (int i = 1; i <= n; i++) {
            scanf("%d", &k[i]);
            sum[i] = sum[i-1] + k[i];
        }
        scanf("%d", &q);
        while (q--) {
            scanf("%d", &d);
            if (d*m > sum[n]) {
                d = (sum[n]+m-1) / m;
            }
            int index = upper_bound(sum+1, sum+n+1, d*m) - sum;
            printf("%d %d\n", index-1, d*m-sum[index-1]);
        }
    }
    return 0;
}
