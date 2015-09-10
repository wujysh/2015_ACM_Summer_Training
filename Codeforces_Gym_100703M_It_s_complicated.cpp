#include <iostream>
#include <cstdio>
using namespace std;

const int MAXN = 15;
int n, q[MAXN], c[MAXN], p[MAXN];

int main() {

    while (~scanf("%d", &n)) {
        for (int i = 0; i < n; i++) {
            scanf("%d", &q[i]);
        }
        for (int i = 0; i < n; i++) {
            scanf("%d", &c[i]);
        }
        for (int i = 0; i < n; i++) {
            scanf("%d", &p[i]);
        }

        double maxa = 0;
        int index;
        for (int i = 0; i < n; i++) {
            double a = (double) q[i] / c[i];
            if (a > maxa) {
                maxa = a;
                index = i;
            }
        }

        int x = (double) (q[index] + c[index] - 1) / c[index];

        int ans = 0;
        for (int i = 0; i < n; i++) {
            ans += p[i] * (x * c[i] - q[i]);
        }

        printf("%d\n", ans);
    }
    return 0;
}
