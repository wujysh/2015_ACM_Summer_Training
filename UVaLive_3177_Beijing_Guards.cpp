#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

const int MAXN = 100010;

int n, a[MAXN], ans;

void input() {
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
}

bool judge2(int x) {
    static int left[MAXN], right[MAXN];

    int A = a[0];
    left[0] = A;  // choose in 1, 2, ..., a[0]
    right[0] = 0; // choose in a[0]+1, a[0]+2, ... x

    for (int i = 1; i < n; i++) {
        if (i % 2 == 1) {
            left[i] = min(a[i], A-left[i-1]);
            right[i] = a[i] - left[i];
        } else {
            right[i] = min(a[i], x-A-right[i-1]);
            left[i] = a[i] - right[i];
        }
        if (left[i] + right[i] < a[i]) {
            return false;
        }
    }

    return left[n-1] == 0;
}

bool judge(int x) {
    static bool vis[3][MAXN * 3];
    static int cnt[3];

    memset(vis[0], false, sizeof(vis[0]));
    memset(vis[2], false, sizeof(vis[2]));
    cnt[0] = cnt[2] = 0;
    for (int i = 1; i <= x; i++) {
        vis[0][i] = vis[2][i] = true;
        cnt[0]++;
        cnt[2]++;
        if (cnt[0] >= a[0]) {
            break;
        }
    }
    if (cnt[0] < a[0]) {
        return false;
    }

    int cur = 1, pre = 0;
    for (int i = 1; i < n-1; i++) {
        memset(vis[cur], false, sizeof(vis[cur]));
        cnt[cur] = 0;

        if (i % 2 == 1) {
            for (int j = 1; j <= x; j++) {
                if (!vis[pre][j]) {
                    vis[cur][j] = true;
                    if (++cnt[cur] >= a[i]) {
                        break;
                    }
                }
            }
            if (cnt[cur] < a[i]) {
                return false;
            }
        } else {
            for (int j = x; j >= 1; j--) {
                if (!vis[pre][j]) {
                    vis[cur][j] = true;
                    if (++cnt[cur] >= a[i]) {
                        break;
                    }
                }
            }
            if (cnt[cur] < a[i]) {
                return false;
            }
        }

        pre = cur;
        cur = 1 - cur;
    }

    memset(vis[cur], false, sizeof(vis[cur]));
    cnt[cur] = 0;
    for (int j = x; j >= 1; j--) {
        if (!vis[pre][j] && !vis[2][j]) {
            vis[cur][j] = true;
            if (++cnt[cur] >= a[n-1]) {
                break;
            }
        }
    }
    if (cnt[cur] < a[n-1]) {
        return false;
    }

    return true;
}

void solve() {
    if (n == 1) {
        printf("%d\n", a[0]);
        return;
    }

    if (n % 2 == 0) {
        ans = a[0] + a[n-1];
        for (int i = 1; i < n; i++) {
            ans = max(ans, a[i-1] + a[i]);
        }
    } else {
        int l = a[0] + a[n-1], r = 3 * a[0];
        for (int i = 1; i < n; i++) {
            l = max(l, a[i-1] + a[i]);
            r = max(r, 3 * a[i]);
        }
        while (l < r) {
            int mid = (l + r) >> 1;
            if (judge2(mid)) {
                r = mid;
            } else {
                l = mid + 1;
            }
        }
        ans = l;
    }

    printf("%d\n", ans);
}

int main() {
    while (~scanf("%d", &n) && n) {
        input();
        solve();
    }
    return 0;
}
