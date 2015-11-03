#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

const int MAXN = 110;

char graph[3][MAXN];
bool dp[MAXN][3];
int n, k, nCase;

void init() {
    memset(dp, false, sizeof(dp));
}

void input() {
    scanf("%d%d", &n, &k);
    for (int i = 0; i < 3; i++) {
        scanf("%s", graph[i]);
    }
}

void solve() {
    for (int i = 0; i < 3; i++) {
        if (graph[i][0] == 's') {
            dp[0][i] = true;
            break;
        }
    }
    for (int i = 3; i < n; i++) {
        for (int j = 0; j < 3; j++) {
            if (graph[j][i] != '.') continue;
            if (j >= 1) {
                dp[i][j] |= dp[i-3][j-1];
            }
            dp[i][j] |= dp[i-3][j];
            if (j <= 1) {
                dp[i][j] |= dp[i-3][j+1];
            }
        }
    }

    for (int i = 0; i < 3; i++) {
        if (dp[n-1][i]) {
            printf("YES\n");
            return;
        }
    }
    printf("NO\n");
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
