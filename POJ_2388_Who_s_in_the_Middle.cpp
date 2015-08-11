#include <algorithm>
#include <iostream>
#include <cstdio>
using namespace std;

const int MAXN = 10010;
int a[MAXN], n;

void input() {
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
}

void solve() {
    sort(a, a+n);
    printf("%d\n", a[n/2]);
}

int main() {
    while (~scanf("%d", &n)) {
        input();
        solve();
    }
    return 0;
}

