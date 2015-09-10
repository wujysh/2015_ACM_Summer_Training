#include <iostream>
#include <cstdio>
using namespace std;

const int MAXN = 310;
int n, ans[MAXN];

void init() {
    ans[0] = ans[1] = 1;
    for (int i = 3; i < MAXN; i += 2) {
        for (int j = MAXN-1; j >= 0; j--) {
            if (i + j < MAXN) {
                ans[i+j] += ans[j];
            }
        }
    }
}

int main() {
    init();
    while (~scanf("%d", &n)) {
        printf("%d\n", ans[n]);
    }
    return 0;
}
