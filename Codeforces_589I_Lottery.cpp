#include <bits/stdc++.h>
using namespace std;

const int MAXN = 110;

int n, k, cnt[MAXN];

int main() {
    while (~scanf("%d%d", &n, &k)) {
        int ave = n / k, ans = 0;
        memset(cnt, 0, sizeof(cnt));

        for (int i = 0; i < n; i++) {
            int c;
            scanf("%d", &c);
            cnt[c]++;
        }

        for (int i = 1; i <= k; i++) {
            if (cnt[i] > ave) {
                ans += cnt[i] - ave;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
