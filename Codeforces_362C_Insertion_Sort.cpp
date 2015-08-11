#include <iostream>
#include <cstdio>
using namespace std;

const int MAXN = 5010;
const int INF = 0x3f3f3f3f;

int n, a[MAXN], gt[MAXN][MAXN], le[MAXN][MAXN];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }

    for (int i = 1; i <= n; i++) {
        gt[i][0] = 0;
        for (int j = 1; j <= n; j++) {
            gt[i][j] = gt[i][j - 1] + (a[j] > a[i]); // gt[i][j]: 在a[0]~a[j]之间有多少个数大于a[i]
            le[i][j] = le[i][j - 1] + (a[j] < a[i]); // le[i][j]: 在a[0]~a[j]之间有多少个数小于a[i]
        }
    }

    int cur = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (a[i] > a[j]) {
                cur++;
            }
        }
    }

    int ans = INF, cnt;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (a[i] > a[j]) {
                int tmp = cur + (le[j][j - 1] - le[j][i] + gt[i][j - 1] - gt[i][i]) - (gt[j][j - 1] - gt[j][i] + le[i][j - 1] - le[i][i]) - 1;
                if (tmp < ans) {
                    ans = tmp;
                    cnt = 1;
                } else if (tmp == ans) {
                    cnt++;
                }
            }
        }
    }

    printf("%d %d\n", ans, cnt);

    return 0;
}
