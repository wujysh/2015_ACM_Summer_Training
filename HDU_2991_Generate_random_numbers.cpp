#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

const int MAXN = 1010;

int n, a[MAXN], a2[MAXN];

void init() {
    memset(a, 0, sizeof(a));
    memset(a2, 0, sizeof(a2));
}

void solve() {
    a[0] = n;
    for (int i = 0; i < MAXN; i++) {
        a2[i] = a[i] * a[i];
        a[i+1] = a2[i] / 100 - (a2[i] / 1000000) * 10000;
    }

    bool flag = false;
    int ans = 0;
    for (int i = 0; i < MAXN; i++) {
        for (int j = i+1; j < MAXN; j++) {
            if (a[i] == a[j]) {
                flag = true;
                ans = j;
                break;
            }
        }
        if (flag) {
            break;
        }
    }

    printf("%d\n", ans);
}

int main() {
    while (~scanf("%d", &n) && n) {
        init();
        solve();
    }
    return 0;
}
