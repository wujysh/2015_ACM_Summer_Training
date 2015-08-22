#include <iostream>
#include <cstdio>
using namespace std;

const int MAXN = 30;

int nCase, n, a[MAXN], ans;

void init() {
    ans = 0;
}

void input() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
}

void solve() {
    bool flag = true;
    for (int i = 0; i < n; i++) {
        if (a[i] != 0) {
            flag = false;
            break;
        }
    }
    if (flag) {
        printf("ap!\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        for (int j = n-1; j >= i+1; j--) {
            a[j] = a[j] - a[j-1];
        }
        ans++;
        bool flag = false;
        for (int j = i+1; j < n; j++) {
            if (a[j]) {
                flag = true;
                break;
            }
        }
        if (!flag) break;
    }

    if (a[n-1] > 0) {
        printf("*fizzle*\n");
        return;
    }
    if (a[n-1] < 0) {
        printf("*bunny*\n");
        return;
    }

    for (int j = 0; j < ans; j++) {
        printf("z");
    }
    printf("ap!\n");
}

int main() {
    scanf("%d", &nCase);
    while (nCase--) {
        init();
        input();
        solve();
    }
    return 0;
}
