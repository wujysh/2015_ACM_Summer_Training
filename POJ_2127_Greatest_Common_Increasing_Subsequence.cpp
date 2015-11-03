#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
using namespace std;

const int MAXN = 510;

int m1, m2, a[MAXN], b[MAXN], pre[MAXN][MAXN], dp[MAXN][MAXN];

void init() {
    memset(dp, 0, sizeof(dp));
    memset(pre, -1, sizeof(dp));
}

void input() {
    for (int i = 1; i <= m1; i++) {
        scanf("%d", &a[i]);
    }
    scanf("%d", &m2);
    for (int i = 1; i <= m2; i++) {
        scanf("%d", &b[i]);
    }
}

vector<int> LCIS(int len1, int len2) {
    int ans = 0, ansi = 0, ansj = 0;

    for (int i = 1; i <= len1; i++) {
        int maxv = 0, index = 1;
        for (int j = 1; j <= len2; j++) {
            dp[i][j] = dp[i-1][j];
            if (b[j] < a[i] && maxv < dp[i-1][j]) {
                maxv = dp[i-1][j];
                index = j;
            } else if (a[i] == b[j]) {
                dp[i][j] = maxv + 1;
                pre[i][j] = index;
            }
            if (dp[i][j] > ans) {
                ans = dp[i][j];
                ansi = i;
                ansj = j;
            }
        }
    }

    vector<int> v;
    while (ans) {
        if (pre[ansi][ansj] != -1) {
            v.push_back(b[ansj]);
            ans--;
            ansj = pre[ansi][ansj];
        }
        ansi--;
    }
    return v;
}

void solve() {
    vector<int> ans = LCIS(m1, m2);
    int len = ans.size();
    printf("%d\n", len);
    if (len == 0) {
        printf("\n");
    } else {
        for (int i = len-1; i > 0; i--) {
            printf("%d ", ans[i]);
        }
        printf("%d\n", ans[0]);
    }
}

int main() {
    while (~scanf("%d", &m1)) {
        init();
        input();
        solve();
    }
    return 0;
}
