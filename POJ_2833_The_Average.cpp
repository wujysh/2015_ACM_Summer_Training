#include <algorithm>
#include <iostream>
#include <cstdio>
using namespace std;

const int MAXN = 15;
const int INF = 0x3f3f3f3f;
int n, n1, n2, Max[MAXN], Min[MAXN];
double sum;

bool cmp(int a, int b) {
    return a > b;
}

void init() {
    sum = 0;
    for (int i = 0; i < MAXN; i++) {
        Max[i] = 0;
        Min[i] = INF;
    }
}

void solve() {
    for (int i = 0; i < n; i++) {
        int a;
        scanf("%d", &a);
        sum += a;
        if (a > Max[n1]) {
            Max[n1] = a;
            make_heap(Max, Max+n1+1, cmp);
            pop_heap(Max, Max+n1+1, cmp);
        }
        if (a < Min[n2]) {
            Min[n2] = a;
            make_heap(Min, Min+n2+1);
            pop_heap(Min, Min+n2+1);
        }
    }

    for (int i = 0; i < n1; i++) {
        //printf("%d ", Max[i]);
        sum -= Max[i];
    }
    //printf("\n");
    for (int i = 0; i < n2; i++) {
        //printf("%d ", Min[i]);
        sum -= Min[i];
    }
    //printf("\n");
    n -= n1 + n2;

    printf("%.6f\n", sum / n);
}

int main() {
    while (~scanf("%d%d%d", &n1, &n2, &n) && (n1 || n2 || n)) {
        init();
        solve();
    }
    return 0;
}
