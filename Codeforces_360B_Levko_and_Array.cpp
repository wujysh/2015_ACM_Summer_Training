#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

const int MAXN = 2010;
int n, k, a[MAXN], dp[MAXN];

void input() {
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
}

// dp[i]: 前i个数，a[i]不进行修改时的最小修改次数
bool judge(long long C) {
    for (int i = 1; i <= n; i++) {  // 初始状态：全部修改
        dp[i] = i - 1;
    }

    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= i - 1; j++) {
            if (abs(a[i] - a[j]) <= C * (i - j)) {
                dp[i] = min(dp[i], dp[j] + i - j - 1);  // 上一个不修改的位置是j，i和j之间都修改。
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        if (dp[i] + n - i <= k) {
            return true;
        }
    }
    return false;
}


void solve() {
    long long l = 0, r = 2e9;
    while (l <= r) {
        long long mid = (l + r) >> 1;
        if (judge(mid)) {
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    printf("%I64d\n", l);
}

int main() {
    while (~scanf("%d%d", &n, &k)) {
        input();
        solve();
    }
    return 0;
}
