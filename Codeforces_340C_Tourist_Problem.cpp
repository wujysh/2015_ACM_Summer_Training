#include <algorithm>
#include <iostream>
#include <cstdio>
using namespace std;

const int MAXN = 100010;

int n, a[MAXN];

long long gcd(long long a, long long b) {
    return b == 0 ? a : gcd(b, a % b);
}

void input() {
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
}

void solve() {
    sort(a+1, a+n+1);
    long long ans1 = 0, ans2 = 0, temp = 0;
    for (int i = 1; i <= n; i++) {
        ans1 += a[i];
        temp += (a[i] - a[i-1]) * (i-1);
        ans2 += temp * 2;
    }

    long long g = gcd(ans1+ans2, n);
    printf("%I64d %I64d\n", (ans1+ans2) / g, n / g);
}

int main() {
    while (~scanf("%d", &n)) {
        input();
        solve();
    }
    return 0;
}
